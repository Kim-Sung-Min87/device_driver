#include "gmock/gmock.h"
#include "device_driver.h"
#include <stdexcept>

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };

	EXPECT_CALL(hardware, read(0xFF))
		.WillRepeatedly(Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST(DeviceDriver, WriteToHW) {
	// TODO : replace hardware with a Test Double
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, write(0xFF, 0xAB))
		.Times(1);
	driver.write(0xFF, 0xAB);
}

TEST(DeviceDriver, ReadFromHW5TimesJustCall) {
	// TODO : replace hardware with a Test Double
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read(0xFF))
		.Times(5);

	driver.read(0xFF);
}

TEST(DeviceDriver, ReadFromHW5TimesSameReturn) {
	// TODO : replace hardware with a Test Double
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read(0xFF))
		.Times(5)
		.WillRepeatedly(Return(41));

	int ret = driver.read(0xFF);

	EXPECT_EQ(41, ret);
}

TEST(DeviceDriver, ReadFromHW5TimesException) {
	// TODO : replace hardware with a Test Double
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read(0xFF))
		.Times(5)
		.WillOnce(Return(41))
		.WillOnce(Return(41))
		.WillOnce(Return(41))
		.WillOnce(Return(41))
		.WillRepeatedly(Return(33));

	EXPECT_THROW(driver.read(0xFF), ReadFailException);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}