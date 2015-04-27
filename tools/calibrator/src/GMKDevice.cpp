#include "GMKDevice.h"

#include <glog/logging.h>

#include "lusb.h"

#include "common.h"


GMKDevice::Descriptor::~Descriptor() {
	libusb_unref_device(d_dev);
}

GMKDevice::Descriptor::Descriptor(libusb_device * dev) 
	: d_dev(libusb_ref_device(dev)) {
}

void GMKDevice::ListDevices(List & ll) {
	ll.clear();
	throw_nyi();
}

GMKDevice::Ptr GMKDevice::Open(const Descriptor::Ptr & handle)  {
	Ptr result = std::make_shared<GMKDevice>();
	lusb_call(libusb_open,handle->d_dev,&(result->d_handle));
	return result;
}

GMKDevice::~GMKDevice() {
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


