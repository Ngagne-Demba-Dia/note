#include <dht.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;
#define DHT11_PIN 7
const int RelaisPin = 6;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(6, OUTPUT);
}
void loop() { 
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  Serial.println("Temp: ");
  Serial.println(DHT.temperature);
  Serial.println("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.println("%");
  if (DHT.temperature >= 30 && DHT.temperature <= 90) // si DHT.temperature. est = ou sup. a 10 ET DHT.temperature infer. ou = a 52 relais ouvert
  {
    digitalWrite(RelaisPin, HIGH);
  }
  else
  {
    digitalWrite(RelaisPin, LOW); // Sinon relais fermé
  }
  delay(1000);
}
