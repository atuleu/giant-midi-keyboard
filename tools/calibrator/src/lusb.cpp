#include "lusb.h"



LibUsbError::LibUsbError(libusb_error e) 
	: std::runtime_error(std::string("libusb: ") + libusb_error_name(e))
	, d_error(e) {
}
	

LibUsbError::LibUsbError(libusb_error e, const std::string & context) 
	: std::runtime_error(context + ": libusb: " + libusb_error_name(e))
	, d_error(e) {
}


LibUsbError::~LibUsbError() throw(){
}


libusb_error LibUsbError::Error() const throw() {
	return d_error;
}
