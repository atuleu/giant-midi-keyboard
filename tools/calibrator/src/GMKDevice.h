#pragma once

#include <memory>
#include <vector>
#include <ostream>

#include <libusb.h> 

#include <communication/communication.h>



class GMKDevice {
public :
	class Descriptor {
	public :
		typedef std::shared_ptr<Descriptor>  Ptr;
		~Descriptor();
		uint16_t BusAndAddress() const;
	private :
		friend class GMKDevice;
		Descriptor(libusb_device * dev);
		libusb_device * d_dev;
		uint16_t d_busAndAddress;
	};

	typedef std::shared_ptr<GMKDevice> Ptr;
	typedef std::vector<Descriptor::Ptr> List;
	~GMKDevice();
	
	static void ListDevices(List & );
	static Ptr Open( const Descriptor::Ptr & handle);

	uint16_t GetParam() const;
	void SetParam() const;
	void SaveInEEPROM() const;

protected :

private :
friend std::ostream & operator<< ( std::ostream & out, const GMKDevice & );
	libusb_device_handle * d_handle;
	Descriptor::Ptr        d_descriptor;
}; 

std::ostream & operator << ( std::ostream & out , const GMKDevice::Descriptor & desc) ;
std::ostream & operator<< ( std::ostream & out, const GMKDevice & );
