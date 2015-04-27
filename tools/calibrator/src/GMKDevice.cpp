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
		LOG(INFO) << "Found at " << *gmkDesc;
		             
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
