// Déclaration des broches
const int Feured = 2;
const int Feuorange = 3;
const int Feugreen = 4;
const int redPedestrian = 5;
const int greenPedestrian = 6;
const int button = 7;

void setup() {
  // Définir les LED comme sorties
  pinMode(Feured, OUTPUT);
  pinMode(Feuorange, OUTPUT);
  pinMode(Feugreen, OUTPUT);
  pinMode(redPedestrian, OUTPUT);
  pinMode(greenPedestrian, OUTPUT);

  // Bouton comme entrée
  pinMode(button, INPUT);

  // État initial
  digitalWrite(Feugreen, HIGH);
  digitalWrite(redPedestrian, HIGH);
}

void loop() {
  if (digitalRead(button) == HIGH) {
    // Passage demandé par un piéton

    // Arrêt du trafic voiture
    digitalWrite(Feugreen, LOW);
    digitalWrite(Feuorange, HIGH);
    delay(1000);
    digitalWrite(Feuorange, LOW);
    digitalWrite(Feured, HIGH);

    // Feu piéton vert ON
    digitalWrite(redPedestrian, LOW);
    digitalWrite(greenPedestrian, HIGH);
    delay(5000);

    // Fin traversée piéton
    digitalWrite(greenPedestrian, LOW);
    digitalWrite(redPedestrian, HIGH);

    // Reprise du trafic voiture
    digitalWrite(Feured, LOW);
    digitalWrite(Feugreen, HIGH);
  }
}
