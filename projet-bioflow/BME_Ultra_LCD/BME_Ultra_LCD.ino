#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === Écran OLED ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset non utilisé
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === Capteur BME280 ===
Adafruit_BME280 bme; // I2C
#define SEALEVELPRESSURE_HPA (1013.25)

// === Capteur Ultrason JSN-SR04T ===
#define trigPin  5   // GPIO5 - D3 sur certaines cartes
#define echoPin  4   // GPIO4 - D2 sur certaines cartes

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation des capteurs...");

  // --- OLED ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adresse I2C de l'OLED
    Serial.println("Erreur: écran OLED non détecté !");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);      // Taille du texte
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initialisation...");
  display.display();
  delay(1000);

  // --- BME280 ---
  if (!bme.begin(0x77)) {   
    Serial.println("Erreur: capteur BME280 introuvable !");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("BME280 introuvable !");
    display.display();
    while (1);
  }

  // --- Ultrason ---
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Capteurs initialisés !");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Capteurs OK !");
  display.display();
  delay(1000);
}

void loop() {
  // --- Lecture BME280 ---
  float temperature = bme.readTemperature();
  float humidite    = bme.readHumidity();
  float pression    = bme.readPressure() / 100.0F;

  // --- Lecture JSN-SR04T ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  if (duration == 0) {
    distance = -1; // Pas de lecture
  } else {
    distance = duration * 0.0344 / 2;
  }

  // --- Affichage série ---
  Serial.println("------ Données capteurs ------");
  Serial.print("Température : "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidité    : "); Serial.print(humidite);    Serial.println(" %");
  Serial.print("Pression    : "); Serial.print(pression);    Serial.println(" hPa");
  Serial.print("Distance    : ");
  if (distance >= 0) {
    Serial.print(distance); Serial.println(" cm");
  } else {
    Serial.println("Erreur de mesure");
  }
  Serial.println("-------------------------------\n");

  // --- Affichage OLED ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp : "); display.print(temperature); display.println(" C");
  display.print("Hum  : "); display.print(humidite);    display.println(" %");
  display.print("Pres : "); display.print(pression);    display.println(" hPa");
  display.print("Dist : ");
  if (distance >= 0) {
    display.print(distance); display.println(" cm");
  } else {
    display.println("Erreur");
  }
  display.display();

  delay(2000);
}
