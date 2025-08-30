const int led1 = 3;       // LED 1 = lumière faible
const int led2 = 4;       // LED 2 = lumière forte
const int photor = A5;    // Capteur LDR

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lecture LDR démarrée...");
}

void loop() {
  int LDRvalue = analogRead(photor);
  Serial.print("Valeur LDR : ");
  Serial.print(LDRvalue);
  Serial.print(" | ");

  int position = map(LDRvalue, 0, 1023, 0, 50);
  for (int i = 0; i < 50; i++) {
    if (i == position) {
      Serial.print("*");
    } else {
      Serial.print("-");
    }
  }
  Serial.println();

  // Contrôle des LEDs
  if (LDRvalue < 500) {
    digitalWrite(led1, HIGH); // LED 1 allumée (faible lumière)
    digitalWrite(led2, LOW);
    Serial.println("LED1 : ON - LED2 : OFF");
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH); // LED 2 allumée (forte lumière)
    Serial.println("LED1 : OFF - LED2 : ON");
  }

  delay(500);
}
