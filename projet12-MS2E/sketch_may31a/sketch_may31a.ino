#include <DHT.h>
#include <LiquidCrystal.h>

// Déclaration de l'écran LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Déclaration des constantes
#define DHTPIN 7        // Broche du capteur DHT
#define DHTTYPE DHT11   // Type du capteur

DHT dht(DHTPIN, DHTTYPE); // Création de l'objet DHT

const int RelaisPin = 6;  // Broche du relais

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(RelaisPin, OUTPUT);
  dht.begin(); // Initialisation du capteur
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223); // Symbole °
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  Serial.print("Temp: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  if (temperature >= 30 && temperature <= 90) {
    digitalWrite(RelaisPin, HIGH); // Relais activé
  } else {
    digitalWrite(RelaisPin, LOW);  // Relais désactivé
  }

  delay(2000);
}
