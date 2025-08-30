// La LED est reliee sur la broche 2 de l'Arduino Uno
#define BROCHE_LED_ROUGE 2
void setup() {
  // Declare la broche sur laquelle la LED est  
  // reliee comme une sortie de l'Arduino Uno
  pinMode(BROCHE_LED_ROUGE, OUTPUT);
}
void loop() {
  // Passer le sortie de l'Arduino à l'état HAUT pour allumer la LED
  digitalWrite(BROCHE_LED_ROUGE, HIGH);
  
  // Attendre 1 seconde, pendant ce temps le processeur ne fait rien
  // et la LED reste donc allumee
  delay(1000);
  
  // Passer le sortie de l'Arduino à l'état BAS pour eteindre la LED
  digitalWrite(BROCHE_LED_ROUGE, LOW);    
  // Attendre 1 seconde, pendant ce temps le processeur ne fait rien
  // et la LED reste donc éteinte
  delay(1000);
}
