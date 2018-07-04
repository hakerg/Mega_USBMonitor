/*
 Name:		Mega_USBMonitor.ino
 Created:	29.06.2018 19:07:14
 Author:	DELL
*/

#include <marekburiak-ILI9341_due-c36b9f3\ILI9341_due.h>
#include <URTouch.h>

#define T_CLK   3
#define T_CS    4
#define T_MOSI  5
#define T_MISO  6
#define T_IRQ   7
#define TFT_DC  9
#define TFT_CS 10

ILI9341_due tft(TFT_CS, TFT_DC);
URTouch ts(T_CLK, T_CS, T_MOSI, T_MISO, T_IRQ);

bool portrait = false;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(500000);
	tft.begin();
	tft.setRotation(iliRotation90);
	ts.InitTouch(LANDSCAPE);
	ts.setPrecision(PREC_LOW);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	tft.fillScreen(tft.color565(127, 127, 127));
}

// the loop function runs over and over again until power down or reset
void loop() {
	uint16_t x, y, size;
	uint8_t mode;

	while (Serial.available() < 1);
	mode = Serial.read();

	if (mode == 'T')
	{
		int16_t data[2];
		if (ts.dataAvailable())
		{
			ts.read();
			data[0] = ts.TP_X;
			data[1] = ts.TP_Y;
		}
		else
		{
			data[0] = -1;
			data[1] = -1;
		}
		Serial.write((uint8_t*)data, 4);
	}
	else if (mode == 'L')
	{
		tft.setRotation(iliRotation90);
		portrait = false;
	}
	else if (mode == 'P')
	{
		tft.setRotation(iliRotation0);
		portrait = true;
	}
	else
	{
		if (portrait)
		{
			while (Serial.available() < 4);
			y = Serial.read() + Serial.read() * 256;
			x = Serial.read();
		}
		else
		{
			while (Serial.available() < 4);
			x = Serial.read() + Serial.read() * 256;
			y = Serial.read();
		}
		size = Serial.read() + 1;
		if (mode == '0')
		{
			while (Serial.available() < 2);
			tft.fillRect(x, y, size, size, Serial.read() + Serial.read() * 256);
		}
		else
		{
			tft.setAddrWindowRect(x, y, size * 4, size);
			size *= size;
			for (; size; size--)
			{
				while (Serial.available() < 2);
				uint16_t color = Serial.read() + Serial.read() * 256;
				tft.pushColor(color);
				tft.pushColor(color);
				tft.pushColor(color);
				tft.pushColor(color);
			}
		}
	}
}
