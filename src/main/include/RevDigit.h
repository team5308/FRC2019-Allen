/*
 * RevDigitBoard.h
 *
 *  Created on: Feb 21, 2017
 *      Author: steve
 * 
 * 	Modified by: Cetian Liu
 *  @github: Wu_Yuanhun
 */

#ifndef SRC_UTIL_REVDIGIT_H_
#define SRC_UTIL_REVDIGIT_H_

#include <frc/I2C.h>
#include <frc/DigitalInput.h>
#include <frc/AnalogInput.h>
#include <chrono>
#include <thread>

using frc::I2C;
using frc::DigitalInput;
using frc::AnalogInput;

class RevDigit {
public:
	static std::shared_ptr<RevDigit> self;
	static std::shared_ptr<RevDigit> GetInstance();
	static int last_volt;
	static bool last_A;
	static bool last_B;
	
	RevDigit();
	void Init();
	void Display(const char* message);
	void Display(const double voltage);
	bool GetA();
	bool GetB();
	double GetPotVoltage();


	bool GetAPressed();
	bool GetBPressed();

private:
	I2C *i2c;
	DigitalInput *aButton;
	DigitalInput *bButton;
	AnalogInput *pot;

	static constexpr uint8_t HT16K33_CMD_BRIGHTNESS = 0xE0;
	static constexpr uint8_t HT16K33_BLINK_CMD = 0x80;
	static constexpr uint8_t HT16K33_BLINK_DISPLAYON = 0x01;
	static const uint16_t alphafonttable[];

	static constexpr int ADDRESS = 0x70;
	static constexpr int BUTTON_A = 19;
	static constexpr int BUTTON_B = 20;
	static constexpr int POTENTIOMETER = 7;
};

#endif /* SRC_UTIL_REVDIGIT_H_ */
