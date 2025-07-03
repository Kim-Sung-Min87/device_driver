#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = (int)(m_hardware->read(address));
    int cmpResult = 0;

    for (int i = 0; i < 4; ++i) {
        cmpResult = (int)(m_hardware->read(address));

        if (cmpResult != result) {
            throw ReadFailException();
		}
	}

    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}