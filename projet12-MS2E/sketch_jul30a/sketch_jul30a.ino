#include <Wire.h>
#include <MPU6050.h>

// --- Déclarations des broches ---
const int flameDigitalPin = 4; // Sortie numérique du capteur de flamme
const int flameAnalogPin  = A0; // Sortie analogique du capteur de flamme
const int buzzerPin       = 5; // Buzzer
const int seuilFlamme     = 500; // Seuil analogique

// --- Déclaration MPU6050 ---
MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  // Initialisation des broches
  pinMode(flameDigitalPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialisation I2C (pour ESP32 : SDA=21, SCL=22)
  Wire.begin(21, 22);
  mpu.initialize();

  // Vérification de la connexion MPU6050
  if (mpu.testConnection()) {
    Serial.println(" MPU6050 connecté !");
  } else {
    Serial.println(" Erreur : pas de connexion MPU6050.");
    while (1); // Stop programme si erreur
  }
}

void loop() {
  // --- Partie capteur de flamme ---
  int flameDigital = digitalRead(flameDigitalPin);
  int flameAnalog = analogRead(flameAnalogPin);

  Serial.print("[ Flamme] Valeur analogique = ");
  Serial.print(flameAnalog);
  Serial.print(" | Numérique = ");
  Serial.print(flameDigital == LOW ? "Pas de flamme" : "Flamme détectée");

  // Allumer le buzzer uniquement si :
  // 1. La flamme est détectée (digital HIGH)
  // 2. La valeur analogique dépasse le seuil
  if (flameDigital == HIGH && flameAnalog > seuilFlamme) {
    Serial.println(" =>  Alerte : Flamme détectée !");
    digitalWrite(buzzerPin, HIGH);
  } else {
    Serial.println(" => OK");
    digitalWrite(buzzerPin, LOW);
  }

  // --- Partie MPU6050 ---
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("[MPU6050] Accélération X = "); Serial.print(ax);
  Serial.print(" | Y = "); Serial.print(ay);
  Serial.print(" | Z = "); Serial.println(az);

  delay(1000);
}
