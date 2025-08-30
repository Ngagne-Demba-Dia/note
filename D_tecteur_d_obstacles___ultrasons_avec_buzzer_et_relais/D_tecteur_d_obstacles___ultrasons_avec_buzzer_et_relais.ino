// Déclaration des broches
#define ECHO_PIN 13
#define TRIG_PIN 11

int buzzerPin = 8;       // Buzzer connecté à la broche 8
int ledPin1 = 6;         // LED 1 connectée à la broche 6
int ledPin2 = 4;         // LED 2 connectée à la broche 4
int relaisPin = A0;      // Relais (électrovanne) connecté à la broche A0

// Variables pour mesurer la distance
int duration;
int distance;

void setup() {
  Serial.begin(9600); // Initialisation de la communication série

  // Configuration des modes des broches
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(relaisPin, OUTPUT);
}

void loop() {
  // Envoi d'une impulsion sur le capteur à ultrasons
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lecture du signal de retour
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Conversion du temps en distance (cm)

  // Conditions selon la distance mesurée
  if (distance >= 60 || distance <= 0) {
    Serial.println("Aucun objet détecté");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(relaisPin, LOW);
  } else {
    Serial.println("Objet détecté");
    Serial.print("Distance = ");
    Serial.println(distance);

    tone(buzzerPin, 400);              // Joue un son de 400 Hz
    digitalWrite(ledPin1, HIGH);       // Allume LED 1
    digitalWrite(ledPin2, LOW);        // Éteint LED 2
    digitalWrite(relaisPin, HIGH);     // Active le relais
  }

  delay(500); // Petite pause pour éviter trop de lectures rapides
}
