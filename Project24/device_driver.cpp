#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = (int)(m_hardware->read(address));
    postConditionCheck(result, address);
    return result;
}

void DeviceDriver::postConditionCheck(int result, long address)
{
    for (int i = 0; i < ADDITIONAL_READ; ++i) {
        if (result == (int)(m_hardware->read(address))) continue;
        throw ReadFailException();
    }
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    preConditionCheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::preConditionCheck(long address)
{
    int result = (int)(m_hardware->read(address));

    if (result != EMPTY_READ) {
        throw WriteFailException();
    }
}
