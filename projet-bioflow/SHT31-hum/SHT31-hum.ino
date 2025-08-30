//#include <Wire.h>
//#include "DFRobot_SHT3x.h"
//
//// Création de l'objet capteur (adresse I2C par défaut 0x44)
//DFRobot_SHT3x sht3x(&Wire, 0x44, 4);
//
//void setup() {
//  Serial.begin(115200);
//
//  // Initialisation I2C sur les broches ESP32 (SDA=21, SCL=22 par défaut)
//  //Wire.begin(21, 22);
//
//  // Vérifier si le capteur répond
//  while (sht3x.begin() != 0) {
//    Serial.println("Échec d'initialisation du SHT3x, vérifier le câblage !");
//    delay(2000);
//  }
//
//  Serial.print("Numéro de série du capteur : ");
//  Serial.println(sht3x.readSerialNumber());
//
//  if (!sht3x.softReset()) {
//    Serial.println("Échec du reset du capteur.");
//  }
//
//  Serial.println("------ Lecture des données SHT3x ------");
//}
//
//void loop() {
//  // Lecture simple
//  Serial.print("Température: ");
//  Serial.print(sht3x.getTemperatureC());
//  Serial.print(" °C / ");
//  Serial.print(sht3x.getTemperatureF());
//  Serial.print(" °F  ");
//
//  Serial.print("Humidité: ");
//  Serial.print(sht3x.getHumidityRH());
//  Serial.println(" %RH");
//
//  // Lecture en mode "high repeatability"
//  DFRobot_SHT3x::sRHAndTemp_t data = sht3x.readTemperatureAndHumidity(DFRobot_SHT3x::eRepeatability_High);
//  if (data.ERR == 0) {
//    Serial.print("Température (mode haute précision): ");
//    Serial.print(data.TemperatureC);
//    Serial.print(" °C / ");
//    Serial.print(data.TemperatureF);
//    Serial.print(" °F  ");
//
//    Serial.print("Humidité: ");
//    Serial.print(data.Humidity);
//    Serial.println(" %RH");
//  }
//
//  delay(1000);
//}

#include <Wire.h>
#include "DFRobot_SHT20.h"

DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);

void setup() {
  Serial.begin(115200);

  // Initialisation du bus I2C (broches par défaut SDA=21, SCL=22)
  Wire.begin(21, 22);

  // Initialisation du capteur
  sht20.initSHT20();
  delay(100);
  Serial.println("Capteur SHT20 initialisé !");
  sht20.checkSHT20();
}

void loop() {
  float humd = sht20.readHumidity();
  float temp = sht20.readTemperature();

  Serial.print("Temps : ");
  Serial.print(millis());
  Serial.print(" ms | Température : ");
  Serial.print(temp, 1);
  Serial.print(" °C | Humidité : ");
  Serial.print(humd, 1);
  Serial.println(" %");

  delay(1000);
}
