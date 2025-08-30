#define trigPin D3   
#define echoPin D2   

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  Serial.begin(115200);
  Serial.println("Mesure de distance avec JSN-SR04T");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // timeout 30ms

  if (duration == 0) {
    Serial.println("Aucun écho reçu !");
  } else {
    distance = duration * 0.0344 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(200);
}
