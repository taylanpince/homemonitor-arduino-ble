#include "Barometer.h"
#include "ble_mini.h"
// #include "DHT.h"
#include <Wire.h>


// #define DHTPIN 2     // what pin we're connected to
// #define DHTTYPE DHT22   // DHT 22  (AM2302)


// DHT dht(DHTPIN, DHTTYPE);
Barometer myBarometer;


void setup() {
	BLEMini_begin(57600);

	// dht.begin();

	myBarometer.init();
}


void loop() {
	uint32_t temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT());
	uint32_t pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());
	uint32_t altitude = myBarometer.calcAltitude(pressure);
	uint32_t atm = pressure / 101325; 
	// uint32_t humidity = dht.readHumidity();
	// uint32_t temperature_alt = dht.readTemperature();

	BLEMini_write(0x0A);
	BLEMini_write(temperature >> 24);
	BLEMini_write(temperature >> 16);
	BLEMini_write(temperature >> 8);
	BLEMini_write(temperature);

	BLEMini_write(0x0B);
	BLEMini_write(pressure >> 24);
	BLEMini_write(pressure >> 16);
	BLEMini_write(pressure >> 8);
	BLEMini_write(pressure);

	BLEMini_write(0x0C);
	BLEMini_write(altitude >> 24);
	BLEMini_write(altitude >> 16);
	BLEMini_write(altitude >> 8);
	BLEMini_write(altitude);

	BLEMini_write(0x0D);
	BLEMini_write(atm >> 24);
	BLEMini_write(atm >> 16);
	BLEMini_write(atm >> 8);
	BLEMini_write(atm);

	delay(1000);
}
