#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Identifiants Wi-Fi
const char* ssid = "Orange-1C9D";
const char* password = "QER71NQ314J";

// Serveur MQTT public HiveMQ
const char* mqtt_server = "broker.hivemq.com";

// Objets WiFi et MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Capteur BME280
Adafruit_BME280 bme;

// Connexion Wi-Fi
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

  Serial.println("\n✅ WiFi connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

// Reconnexion MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX); // ID unique

    if (client.connect(clientId.c_str())) {
      Serial.println(" ✅ Connecté !");
      // message test
      client.publish("capteurs/test", "ESP32 connecté au broker MQTT !");
      // souscrire à un topic si tu veux recevoir des commandes
      client.subscribe("capteurs/commandes");
    } else {
      Serial.print("❌ Échec, code = ");
      Serial.print(client.state());
      Serial.println(" → nouvelle tentative dans 2s");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Initialisation du BME280
  if (!bme.begin(0x77)) {  // Adresse I2C du BME280
    Serial.println("❌ Erreur capteur BME280 !");
    while (1);
  } else {
    Serial.println("✅ Capteur BME280 détecté !");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lecture des données BME280
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float press = bme.readPressure() / 100.0F; // en hPa

  // Création du message JSON
  String payload = "{ \"temperature\": " + String(temp, 2) +
                   ", \"humidity\": " + String(hum, 2) +
                   ", \"pressure\": " + String(press, 2) + " }";

  // Publication sur MQTT
  client.publish("capteurs/bme280", payload.c_str());

  Serial.println("📤 Publié : " + payload);

  delay(5000);  // Publication toutes les 5 secondes
}
