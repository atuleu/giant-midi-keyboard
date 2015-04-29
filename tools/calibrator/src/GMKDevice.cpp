#include "GMKDevice.h"

#include "lusb.h"

std::ostream & operator<<( std::ostream & out, const libusb_device_descriptor & d) {
	out << "Device 0x" << std::hex << (int)d.idVendor << ":0x" << (int)d.idProduct << std::dec;
	return out;
}

#include <glog/logging.h>



#include "common.h"


GMKDevice::Descriptor::~Descriptor() {
	libusb_unref_device(d_dev);
}

GMKDevice::Descriptor::Descriptor(libusb_device * dev) 
	: d_dev(libusb_ref_device(dev)) {
	d_busAndAddress = libusb_get_bus_number(d_dev);
	d_busAndAddress = (d_busAndAddress << 8) | libusb_get_device_address(d_dev);
	FetchStrings();
}


void GMKDevice::Descriptor::FetchStrings() {
	libusb_device_descriptor desc;
	lusb_call(libusb_get_device_descriptor,d_dev,&desc);
	libusb_device_handle * unsafeHandle;
	lusb_call(libusb_open,d_dev,&unsafeHandle);
	//to make sure we close in all cases
	std::shared_ptr<libusb_device_handle> handle(unsafeHandle,[](libusb_device_handle * h){
			libusb_close(h);
		});

	unsigned char buffer[1000];
	lusb_call(libusb_get_string_descriptor_ascii,
	          handle.get(),
	          desc.iManufacturer,
	          buffer,
	          sizeof(buffer));		
	d_iManufacturer = std::string((char*)buffer);

	lusb_call(libusb_get_string_descriptor_ascii,
	          handle.get(),
	          desc.iProduct,
	          buffer,
	          sizeof(buffer));
	d_iProduct = std::string((char*)buffer);
	
}

const std::string & GMKDevice::Descriptor::Product() const {
	return d_iProduct;
}

const std::string & GMKDevice::Descriptor::Manufacturer() const{
	return d_iManufacturer;
}

uint16_t GMKDevice::Descriptor::BusAndAddress() const {
	return d_busAndAddress;
}



void GMKDevice::ListDevices(List & ll) {
	ll.clear();
	LOG(INFO) << "Listing devices with VID:" << std::hex << VID << ", PID:" << PID << std::dec;
	
	libusb_device ** allDevices;

	ssize_t count = libusb_get_device_list(NULL,&allDevices);
	if ( count < 0 ) {
		lusb_throw(libsub_get_device_list,(libusb_error)count);
	}

	ll.reserve(count);

	for ( uint32_t i = 0; i < count; ++i) {
		libusb_device_descriptor desc;
		lusb_call(libusb_get_device_descriptor,allDevices[i],&desc);
		if ( desc.idVendor != VID || desc.idProduct != PID) {
			continue;
		}
		
		Descriptor::Ptr gmkDesc = std::make_shared<Descriptor>(allDevices[i]);
		ll.push_back(gmkDesc);
		LOG(INFO) << "Found '" << gmkDesc->Product()
		          << "' by '" << gmkDesc->Manufacturer()
		          << "'at " << *gmkDesc;
		             
	}

//	throw_nyi();
}

GMKDevice::Ptr GMKDevice::Open(const Descriptor::Ptr & handle)  {
	Ptr result = std::make_shared<GMKDevice>();
	lusb_call(libusb_open,handle->d_dev,&(result->d_handle));
	result->d_descriptor = handle;
	LOG(INFO) << "Opened " << *result;
	return result;
}

GMKDevice::~GMKDevice() {
	LOG(INFO) << "Closing " << *this;
	libusb_close(d_handle);
}

uint16_t GMKDevice::GetParam() const {
	throw_nyi();
}

void GMKDevice::SetParam() const {
	throw_nyi();
}

void GMKDevice::SaveInEEPROM() const {
	throw_nyi();
}

std::ostream & operator << ( std::ostream & out , const GMKDevice::Descriptor & desc) {
	int bus = desc.BusAndAddress();
	int address = bus & 0xff;
	bus = bus >> 8;
	return out << bus << ":" << address;
}

std::ostream & operator << (std::ostream & out, const GMKDevice & d) {
	if (! d.d_descriptor ) {
		return out << "Unoppenned GMKDevice";
	}
	return out << "GMKDevice " << *d.d_descriptor;
}


uint16_t GMKDevice::BusAndAddress() const {
	return d_descriptor->BusAndAddress();
}

#include <sstream>

void GMKDevice::FetchCellStatus(int key, CellStatus_t & value) {
	if (key < 0 || key >= 25) {
		return;
	}
	std::lock_guard<std::mutex> lock(d_mutex);
	
	uint8_t buffer[sizeof(CellStatus_t)];
	

	lusb_call(libusb_control_transfer,
	          d_handle,
	          REQ_VENDOR_IN,
	          GMK_USBIF_INST_FETCH_CELL_STATUS,
	          key,
	          key,
	          buffer,
	          sizeof(CellStatus_t),
	          0);

	std::ostringstream oss;
	std::string prefix = "";
	for (uint8_t i = 0; i < sizeof(CellStatus_t); ++i ) {
		oss << prefix << std::hex << (int) buffer[i];
		prefix = ":";
	}
	LOG(INFO) << "Got: " << oss.str();

	value.systime = ((uint16_t)buffer[1]) << 8 | buffer[0];
	value.value = ((uint16_t)buffer[3]) << 8 | buffer[3];
	value.pressCount = buffer[4];
	value.lastVelocity = buffer[5];

}
