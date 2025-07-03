#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Read operation failed";
    }
};

class WriteFailException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Write operation failed";
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
	static const int ADDITIONAL_READ = 4;
	static const int EMPTY_READ = 0xFF;
    void preConditionCheck(long address);
    void postConditionCheck(int result, long address);
};