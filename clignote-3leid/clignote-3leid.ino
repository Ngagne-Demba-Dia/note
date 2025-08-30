// Clignotement de plusieurs LED 
// https://tutoduino.fr/
// Copyleft 2020
#define BROCHE_LED_ROUGE 2
#define BROCHE_LED_VERTE 3
#define BROCHE_LED_JAUNE 4
void setup() {
  pinMode(BROCHE_LED_VERTE, OUTPUT);
  pinMode(BROCHE_LED_JAUNE, OUTPUT);
  pinMode(BROCHE_LED_ROUGE, OUTPUT);
}
void loop() {
  digitalWrite(BROCHE_LED_ROUGE, HIGH);
  delay(1000); 
  digitalWrite(BROCHE_LED_VERTE, HIGH);
  delay(1000);
  digitalWrite(BROCHE_LED_JAUNE, HIGH);
  delay(1000);
  digitalWrite(BROCHE_LED_VERTE, LOW);    
  digitalWrite(BROCHE_LED_JAUNE, LOW);    
  digitalWrite(BROCHE_LED_ROUGE, LOW);    
  delay(1000);                       
}
