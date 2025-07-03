#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Read operation failed";
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    bool isSameValueRead(int result, long address);
};