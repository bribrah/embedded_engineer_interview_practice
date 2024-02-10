/*
 * CustomUart.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: bespinosa
 */

#include "CustomUart.h"

#define INPUT_PORT UART_input_GPIO_Port
#define INPUT_PIN UART_input_Pin
#define OUTPUT_PORT UART_output_GPIO_Port
#define OUTPUT_PIN UART_output_Pin

CustomUart::CustomUart(uint32_t baudRate) {
	this->baudRate = baudRate;
	waitTime = 1000000 / baudRate;
}
void CustomUart::sendByte(uint8_t byte) {
	// first bit always low
	outputBit(0);
	for (int i = 0; i < 8; i++) {
		outputBit((byte >> i) & 1);
	}

	// stop bit;
	outputBit(1);
}

uint8_t CustomUart::receiveByte(int &status) {
	bool bitRecv;
	uint8_t recvdByte = 0;
	status = 0;

	while (inputBit()) {
	}
	// get the data
	for (int i = 0; i < 8; i++) {
		bitRecv = inputBit();
		recvdByte = (recvdByte) | (bitRecv << i);
	}

	// make sure stop bit
	bitRecv = inputBit();
	if (!bitRecv) {
		// this isnt an end bit!
		status = -1;

		return 0;
	}

	return recvdByte;
}

void CustomUart::outputBit(bool bit) {
	GPIO_PinState state;
	if (bit) {
		state = GPIO_PIN_SET;
	} else {
		state = GPIO_PIN_RESET;
	}
	HAL_GPIO_WritePin(OUTPUT_PORT, OUTPUT_PIN, state);
	bitDelay();
}

bool CustomUart::inputBit() {
	GPIO_PinState state = HAL_GPIO_ReadPin(INPUT_PORT, INPUT_PIN);
	bitDelay();
	return (bool) state;
}

void CustomUart::bitDelay() {
	usec_delay(waitTime);
	return;
}

void recvSendLoop() {
	CustomUart myUart(9600);
	uint8_t recvd;
	int status;
	char buf[100];
	size_t bufPointer;

	while (1) {
		recvd = 0;
		bufPointer = 0;
		while ((char) recvd != '\n') {
			recvd = myUart.receiveByte(status);
			buf[bufPointer] = recvd;
			bufPointer++;
		}
		buf[bufPointer] = '\n';
		for (size_t i = 0; i <= bufPointer; i++) {
			myUart.sendByte(buf[bufPointer]);
		}
		usec_delay(10000);
	}
}
