#include "GMKDevice.h"

#include <glog/logging.h>

#include "lusb.h"

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
	throw_nyi();
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
