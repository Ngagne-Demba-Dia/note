const int flamePin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(flamePin, INPUT);
}

void loop() {
  int flame = digitalRead(flamePin);

  if (flame == LOW) {
    Serial.println("Flamme détectée !");
  } else {
    Serial.println("Pas de flamme.");
  }

  delay(500);
}
