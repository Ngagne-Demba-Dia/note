#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==== OLED ====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ==== BME280 ====
Adafruit_BME280 bme;

// ==== Ultrason JSN-SR04T ====
#define trigPin D3
#define echoPin D2
long duration;
int distance;

// ==== MQ-3 ====
#define PIN_ANALOG_IN A2
int digitalPin = D12;

void setup() {
  Serial.begin(115200);

  // ==== OLED ====
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erreur OLED"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Initialisation..."));
  display.display();

  // ==== BME280 ====
  if (!bme.begin(0x77)) {
    Serial.println("Erreur : BME280 introuvable !");
    display.println("Erreur BME280 !");
    display.display();
    while (true);
  }

  // ==== JSN-SR04T ====
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // ==== MQ-3 ====
  pinMode(digitalPin, INPUT);

  Serial.println("Capteurs prêts !");
  display.println("Capteurs OK !");
  display.display();
  delay(1000);
}

void loop() {
  // === BME280 ===
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0F;

  // === Ultrason ===
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.0344 / 2;
  }

  // === MQ-3 ===
  int digitalVal = digitalRead(digitalPin);
  int adcVal = analogRead(PIN_ANALOG_IN);
  double voltage = adcVal / 4095.0 * 3.3;

  // === Affichage série ===
  Serial.printf("BME280 -> Temp: %.2f °C, Hum: %.2f %%, Pression: %.2f hPa\n", temp, hum, pres);
  if (distance == -1)
    Serial.println("Ultrason -> Aucun écho !");
  else
    Serial.printf("Ultrason -> Distance: %d cm\n", distance);
  Serial.printf("MQ-3 -> Digital: %d, ADC: %d, Voltage: %.2f V ", digitalVal, adcVal, voltage);
  Serial.println(digitalVal ? " (Normal)" : " (Exceeding)");
  Serial.println("--------------------------------------------------");

  // === Affichage OLED ===
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("T: %.1fC  H: %.1f%%\n", temp, hum);
  display.printf("P: %.0f hPa\n", pres);

  if (distance == -1)
    display.print("Dist: -- cm\n");
  else
    display.printf("Dist: %d cm\n", distance);

  display.printf("MQ-3: %.2fV ", voltage);
  display.print(digitalVal ? "OK" : "!!");
  display.display();

  delay(5000);  // rafraîchissement toutes les 5 secondes
}
