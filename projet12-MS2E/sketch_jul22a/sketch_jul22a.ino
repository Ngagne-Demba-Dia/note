#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA=21, SCL=22

  if (!bme.begin(0x76) && !bme.begin(0x77)) {
    Serial.println("BME280 non detecte !");
    while (1);
  }
}

void loop() {
  Serial.print("Temp: "); Serial.print(bme.readTemperature()); Serial.println(" °C");
  Serial.print("Humid: "); Serial.print(bme.readHumidity()); Serial.println(" %");
  Serial.print("Pression: "); Serial.print(bme.readPressure() / 100.0F); Serial.println(" hPa");
  delay(2000);
}
