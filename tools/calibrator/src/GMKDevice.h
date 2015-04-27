#pragma once

#include <memory>
#include <vector>

#include <libusb.h> 

#include <communication/communication.h>



class GMKDevice {
public :
	class Descriptor {
	public :
		typedef std::shared_ptr<Descriptor>  Ptr;
		~Descriptor();

	private :
		friend class GMKDevice;
		Descriptor(libusb_device * dev);
		libusb_device * d_dev;
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
	libusb_device_handle * d_handle;
}; 
