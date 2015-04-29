#pragma once

#include <memory>
#include <vector>
#include <ostream>
#include <mutex>

#include <libusb.h> 

#include <communication/communication.h>



class GMKDevice {
public :
	class Descriptor {
	public :
		typedef std::shared_ptr<Descriptor>  Ptr;
		Descriptor(libusb_device * dev);
		~Descriptor();
		uint16_t BusAndAddress() const;
		const std::string & Product() const;
		const std::string & Manufacturer() const;
		
	private :
		friend class GMKDevice;
		void FetchStrings();
		libusb_device * d_dev;
		uint16_t d_busAndAddress;
		std::string d_iProduct;
		std::string d_iManufacturer;
	};

	typedef std::shared_ptr<GMKDevice> Ptr;
	typedef std::vector<Descriptor::Ptr> List;
	~GMKDevice();
	
	static void ListDevices(List & );
	static Ptr Open( const Descriptor::Ptr & handle);

	uint16_t BusAndAddress() const;

	uint16_t GetParam() const;
	void SetParam() const;
	void SaveInEEPROM() const;

	void FetchCellStatus(int key, CellStatus_t & report);

protected :

private :

	const static uint16_t VID = 0x03eb;
	const static uint16_t PID = 0x2048;


	friend std::ostream & operator<< ( std::ostream & out, const GMKDevice & );
	libusb_device_handle * d_handle;
	Descriptor::Ptr        d_descriptor;

	std::mutex             d_mutex;
}; 

std::ostream & operator << ( std::ostream & out , const GMKDevice::Descriptor & desc) ;
std::ostream & operator<< ( std::ostream & out, const GMKDevice & );
