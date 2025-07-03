#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = (int)(m_hardware->read(address));

    for (int i = 0; i < ADDITIONAL_READ; ++i) {
        if (isSameValueRead(result, address)) continue;
        throw ReadFailException();
	}

    return result;
}

bool DeviceDriver::isSameValueRead(int result, long address)
{
    return result == (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int result = (int)(m_hardware->read(address));
    
    if (result != EMPTY_READ) {
        throw WriteFailException();
	}

    m_hardware->write(address, (unsigned char)data);
}