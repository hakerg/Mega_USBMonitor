# Mega_USBMonitor
This is a project for Arduino MEGA

What do you need:
-Arduino MEGA
-2.4 TFT SPI 240x320 with touchscreen
-5x 10k Ohm resistors
-4x 3.3k Ohm resistors
-4x 1.5k Ohm resistors
-wires


Connection schemat:

VCC -> 3.3V
GND -> GND
CS -> 1.5k Ohm -> Pin 10
CS -> 3.3k Ohm -> GND
RESET -> 3.3V
DC -> 1.5k Ohm -> Pin 9
DC -> 3.3k Ohm -> GND
SDI(MOSI) -> 1.5k Ohm -> Arduino MOSI
SDI(MOSI) -> 3.3k Ohm -> GND
SCK -> 1.5k Ohm -> Arduino SCK
SCK -> 3.3k Ohm -> GND
LED -> 3.3V
SDO(MISO) -> Arduino MISO

Touchscreen:
T_CLK -> 10k Ohm -> Pin 3
T_CS -> 10k Ohm -> Pin 4
T_DIN -> 10k Ohm -> Pin 5
T_DO -> 10k Ohm -> Pin 6
T_IRQ -> 10k Ohm -> Pin 7


ILI9341_due library: http://marekburiak.github.io/ILI9341_due/

You have to set SERIAL_RX_BUFFER_SIZE to 256 in file: \hardware\avr\1.6.21\cores\arduino\HardwareSerial.h
