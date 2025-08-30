#include <Wire.h>
#include <MPU6050.h>

const int flameDigitalPin = 4;
const int flameAnalogPin  = 34;
const int buzzerPin       = 5;
const int seuilFlamme     = 500;

MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  pinMode(flameDigitalPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Wire.begin(21, 22);
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("✅ MPU6050 connecté avec succès !");
  } else {
    Serial.println("❌ Erreur : connexion au MPU6050 échouée.");
  }
}

void loop() {
  int valeurNumerique = digitalRead(flameDigitalPin);
  int valeurAnalogique = analogRead(flameAnalogPin);

  bool flammeDetectee = (valeurNumerique == HIGH || valeurAnalogique > seuilFlamme);

  Serial.print("[Capteur de flamme] Valeur analogique : ");
  Serial.print(valeurAnalogique);
  Serial.print(" | État numérique : ");
  Serial.print(valeurNumerique == HIGH ? "Flamme détectée" : "Pas de flamme");

  if (flammeDetectee) {
    Serial.println(" => 🔥 Flamme détectée - Alerte !");
    digitalWrite(buzzerPin, HIGH);
  } else {
    Serial.println(" => ✅ Pas de flamme détectée.");
    digitalWrite(buzzerPin, LOW);
  }

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("[MPU6050] Accélération X = ");
  Serial.print(ax);
  Serial.print(" | Y = ");
  Serial.print(ay);
  Serial.print(" | Z = ");
  Serial.println(az);

  delay(1000);
}
