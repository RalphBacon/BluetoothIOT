/*
 * Bluetooth HC-06 (SLAVE) control from your Android phone RSB May 2016
 */
#include "Arduino.h"
#include <SoftwareSerial.h>

// Instantiate our BT object. First value is RX pin, second value TX pin
// NOTE: do NOT connect the RX directly to the Arduino unless you are using a
// 3.3v board. In all other cases connect pin 4 to a 1K2 / 2K2 resistor divider
/*
 * ---- pin 6-----> |----1K2----| to HC06 RX |----2K2----| -----> GND
 *
 * See my video at www.youtube.com/c/RalphBacon for more details.
 */
SoftwareSerial BTserial(4, 6); // RX , TX

// Our output indicator (could drive an opto-isolated relay)
byte LEDpin = 8;

// -----------------------------------------------------------------------------------
// SET UP   SET UP   SET UP   SET UP   SET UP   SET UP   SET UP   SET UP   SET UP
// -----------------------------------------------------------------------------------
void setup() {

	// LED output pin
	pinMode(LEDpin, OUTPUT);

	// Serial Windows stuff
	Serial.begin(9600);
	Serial.println("Set up complete");

	// Set baud rate of HC-06 that you set up using the FTDI USB-to-Serial module
	BTserial.begin(9600);
}

// -----------------------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// -----------------------------------------------------------------------------------
void loop() {

	// If the HC-06 has some data (single char) for us, get it
	if (BTserial.available() > 0) {

		// Get the char
		char data = (char) BTserial.read();

		// Depending on value turn LED ON or OFF (or error message)
		switch (data) {

		case '1':
			Serial.println("ON");
			digitalWrite(LEDpin, HIGH);
			break;

		case '0':
			Serial.println("OFF");
			digitalWrite(LEDpin, LOW);
			break;

		default:
			Serial.print("NOT RECOGNISED: ");
			Serial.println(data);
			BTserial.print("Error!");
		}
	}
}
