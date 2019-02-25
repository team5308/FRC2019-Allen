/*
 * RevDigitBoard.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: steve
 * 
 * 	Modified by: Cetian Liu
 */

#include "RevDigit.h"

int RevDigit::last_volt = 0;

/*
 * Creates an instance of the Digit board.  You'll only need one.
 *
 * Thank you to https://github.com/red-green/REVDigitBoard/blob/master/REVDigitBoard.java
 */
RevDigit::RevDigit()
{
	this->i2c = new I2C(I2C::Port::kMXP, ADDRESS);
	this->aButton = new DigitalInput(BUTTON_A);
	this->bButton = new DigitalInput(BUTTON_B);
	this->pot = new AnalogInput(POTENTIOMETER);

	this->Init();

	self.reset(this);
}

void RevDigit::Init() {
	uint8_t osc = 0x21;

	uint8_t b = 0;
	uint8_t blink = HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1);

	uint8_t brightness = 15;
	uint8_t bright = HT16K33_CMD_BRIGHTNESS | brightness;

	this->i2c->WriteBulk(&osc, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	this->i2c->WriteBulk(&blink, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	this->i2c->WriteBulk(&bright, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

/*
 * Show a message on the Digit.
 */
void RevDigit::Display(const char* message) {
	char messageToDisplay[] = "    ";
	if (NULL != message) {
		int length = strlen(message);

		if (length >= 1) {
			messageToDisplay[0] = message[0];
		}
		if (length >= 2) {
			messageToDisplay[1] = message[1];
		}
		if (length >= 3) {
			messageToDisplay[2] = message[2];
		}
		if (length == 4) {
			messageToDisplay[3] = message[3];
		}
	}

	uint8_t msg[10];
	msg[0] = 0b00001111;
	msg[1] = 0b00001111;
	msg[2] = alphafonttable[(int) messageToDisplay[3]] & 0xFF;
	msg[3] = alphafonttable[(int) messageToDisplay[3]] >> 8;
	msg[4] = alphafonttable[(int) messageToDisplay[2]] & 0xFF;
	msg[5] = alphafonttable[(int) messageToDisplay[2]] >> 8;
	msg[6] = alphafonttable[(int) messageToDisplay[1]] & 0xFF;
	msg[7] = alphafonttable[(int) messageToDisplay[1]] >> 8;
	msg[8] = alphafonttable[(int) messageToDisplay[0]] & 0xFF;
	msg[9] = alphafonttable[(int) messageToDisplay[0]] >> 8;

	i2c->WriteBulk(msg, sizeof(msg));
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void RevDigit::Display(const double voltage) 
{
	int volt = ((int) (voltage * 100)) % 10000;
	if(std::abs(volt-last_volt) >= 15)
	{
		char mes[4];
		for(int i=3;i>=0;i--) 
		{
			mes[i] = (char) (volt % 10) + '0';
			volt /= 10;
		}
		this->Display(mes);
	}
	last_volt = volt;
	
	return ;
}

/*
 * Get the state of the A button.
 */
bool RevDigit::GetA() {
	return !this->aButton->Get();
}

/*
 * Get the state of the B button.
 */
bool RevDigit::GetB() {
	return !this->bButton->Get();
}

/*
 * Get the state of the potentiometer.
 */
double RevDigit::GetPotVoltage() {
	return this->pot->GetVoltage();
}

const uint16_t RevDigit::alphafonttable[] = {
		// See Table 2-1 here http://www.revrobotics.com/content/docs/REV-11-1113-UM.pdf

		// Dp L M N K J H G2 G1 F E D C B A
		//  E D C B A 9 8  7  6 5 4 3 2 1 0

		0b0000000000000001,// 0x00
		0b0000000000000010,
		0b0000000000000100,
		0b0000000000001000,
		0b0000000000010000,
		0b0000000000100000,
		0b0000000001000000,
		0b0000000010000000,
		0b0000000100000000,
		0b0000001000000000,
		0b0000010000000000,
		0b0000100000000000,
		0b0001000000000000,
		0b0010000000000000,
		0b0100000000000000,
		0b1000000000000000,
		0b0000000000000000, // 10
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0001001011001001,
		0b0001010111000000,
		0b0001001011111001,
		0b0000000011100011,
		0b0000010100110000,
		0b0001001011001000,
		0b0011101000000000,
		0b0001011100000000,
		0b0000000000000000, // 0x20
		0b0000000000000110, // !
		0b0000001000100000, // "
		0b0001001011001110, // #
		0b0001001011101101, // $
		0b0000110000100100, // %
		0b0010001101011101, // &
		0b0000010000000000, // '
		0b0010010000000000, // (
		0b0000100100000000, // )
		0b0011111111000000, // *
		0b0001001011000000, // +
		0b0000100000000000, // ,
		0b0000000011000000, // -
		0b0000000000000000, // .
		0b0000110000000000, // /
		0b0000000000111111, // 0x30, 0
		0b0000000000000110, // 1
		0b0000000011011011, // 2
		0b0000000011001111, // 3
		0b0000000011100110, // 4
		0b0000000011101101, // 5
		0b0000000011111101, // 6
		0b0000000000000111, // 7
		0b0000000011111111, // 8
		0b0000000011101111, // 9
		0b0001001000000000, // :
		0b0000101000000000, // ;
		0b0010010000000000, // <
		0b0000000011001000, // =
		0b0000100100000000, // >
		0b0001000010000011, // ?
		0b0000001010111011, // 0x40, @
		0b0000000011110111, // A
		0b0001001010001111, // B
		0b0000000000111001, // C
		0b0001001000001111, // D
		0b0000000011111001, // E
		0b0000000011110001, // F
		0b0000000010111101, // G
		0b0000000011110110, // H
		0b0001001000001001, // I
		0b0000000000011110, // J
		0b0000110001110000, // K
		0b0000000000111000, // L
		0b0000010100110110, // M
		0b0000100100110110, // N
		0b0000000000111111, // O
		0b0000000011110011, // 0x50, P
		0b0000100000111111, // Q
		0b0000100011110011, // R
		0b0000000110001101, // S
		0b0001001000000001, // T
		0b0000000000111110, // U
		0b0010010000110000, // V
		0b0010100000110110, // W
		0b0010110100000000, // X
		0b0001010100000000, // Y
		0b0010010000001001, // Z
		0b0000000000111001, // [
		0b0000100100000000, // (backslash)
		0b0000000000001111, // ]
		0b0000000000100011, // ^
		0b0000000000001000, // _
		0b0000000100000000, // 0x60, `

		// Dp L M N K J H G2 G1 F E D C B A
		//  E D C B A 9 8  7  6 5 4 3 2 1 0

		0b0000000011011111, // a
		0b0000000011111100, // b
		0b0000000011011000, // c
		0b0000000011011110, // d
		0b0000000011111011, // e
		0b0000000001110001, // f
		0b0000000110001111, // g
		0b0001000001110000, // h
		0b0001000000000000, // i
		0b0000000000001110, // j
		0b0001111000000000, // k
		0b0000000000110000, // l
		0b0001000011010100, // m
		0b0001000001010000, // n
		0b0000000011011100, // o
		0b0000000101110000, // ox70, p
		0b0000100011100011, // q
		0b0000000001010000, // r
		0b0000000110001101, // s
		0b0000000001111000, // t
		0b0000000000011100, // u
		0b0010000000010000, // v
		0b0010100000010100, // w
		0b0010110100000000, // x
		0b0000000110001110, // y
		0b0010000001001000, // z
		0b0010000101001001, // {
		0b0001001000000000, // |
		0b0000110010001001, // }
		0b0000010100100000, // ~
		0b0011111111111111, };

std::shared_ptr<RevDigit> RevDigit::self;

std::shared_ptr<RevDigit> RevDigit::GetInstance() 
{
	return self;
}