#pragma once

#include <stdexcept>
#include <libusb.h>

class LibUsbError : public std::runtime_error {
public :
	LibUsbError(libusb_error error);
	LibUsbError(libusb_error, const std::string & reason);
	virtual ~LibUsbError() throw();

	libusb_error Error() const throw();
private : 

	libusb_error d_error;
	
};

#define lusb_throw(fnct,error) do { \
	throw LibUsbError(error,"On call of " #fnct "()"); \
}while(0)

#define lusb_call(fnct,...) do { \
	int usbErr_ ## fnct = fnct(__VA_ARGS__); \
	if (usbErr_ ## fnct < 0) { \
		lusb_throw(fnct,(libusb_error) usbErr_ ## fnct); \
	}\
}while(0)

#define l
