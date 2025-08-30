#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

// ==== WIFI CONFIG ====
const char* ssid = "Orange-1C9D";
const char* password = "QER71NQ314J";

// ==== MQTT CONFIG ====
const char* mqtt_server = "broker.hivemq.com";  // ou ton broker
const int mqtt_port = 1883;
const char* mqtt_topic = "capteurs/esp32";

// ==== OBJETS ====
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BME280 bme;

// ==== PINS ULTRASON ====
#define trigPin D3  
#define echoPin D2   

long duration;
int distance;

// ==== WIFI CONNECT ====
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connexion à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

// ==== MQTT CONNECT ====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentative connexion MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connecté !");
    } else {
      Serial.print("ECHEC, rc=");
      Serial.print(client.state());
      Serial.println(" nouvelle tentative dans 5s");
      delay(5000);
    }
  }
}

// ==== MESURE ULTRASON ====
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // timeout 30ms
  if (duration == 0) {
    return -1; // erreur
  } else {
    return duration * 0.0344 / 2;
  }
}

// ==== SETUP ====
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!bme.begin(0x77)) {   
    Serial.println("Impossible de trouver le BME280 !");
    while (1);
  }
}

// ==== LOOP ====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lecture BME280
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // hPa

  // Lecture ultrason
  int distance = getDistance();

  // Construction JSON
  char msg[200];
  if (distance == -1) {
    snprintf(msg, sizeof(msg),
             "{\"temperature\":%.2f, \"humidity\":%.2f, \"pressure\":%.2f, \"distance\":\"no_echo\"}",
             temperature, humidity, pressure);
  } else {
    snprintf(msg, sizeof(msg),
             "{\"temperature\":%.2f, \"humidity\":%.2f, \"pressure\":%.2f, \"distance\":%d}",
             temperature, humidity, pressure, distance);
  }

  // Envoi MQTT
  Serial.print("Publication MQTT : ");
  Serial.println(msg);
  client.publish(mqtt_topic, msg);

  delay(2000); // envoie toutes les 2s
}
