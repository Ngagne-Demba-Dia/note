////#define PIN_ANALOG_IN A0   
//#define PIN_DIGITAL_IN D13  
//void setup() {
//  Serial.begin(115200);
//  pinMode(PIN_DIGITAL_IN, INPUT);
//  Serial.println("MQ-3 initialisé. Stabilisation en cours...");
//  delay(30000); // 30s pour stabilisation du capteur (chauffage)
//  Serial.println("MQ-3 prêt !");
//}
//
//void loop() {
//  int digitalVal = digitalRead(PIN_DIGITAL_IN); // Lecture du seuil digital
////  int adcVal = analogRead(PIN_ANALOG_IN);       // Lecture analogique (0 à 4095)
//  
////  int dacVal = map(adcVal, 0, 4095, 0, 255);     // Conversion en échelle 8 bits (facultatif)
////  float voltage = adcVal / 4095.0 * 3.3;         // Tension en volts
//
//  Serial.print("MQ-3 -> Digital: ");
//  Serial.print(digitalVal == 1 ? "Normal" : "Gaz détecté");
//  Serial.print(" | ADC: ");
////  Serial.print(adcVal);
//  Serial.print(" | Tension: ");
////  Serial.print(voltage, 2);
//  Serial.println(" V");
//
//  delay(500);
//}
#define PIN_ANALOG_IN  A2
int digitalPin =  D12;

//The following two variables hold the digital signal and adc values respectively
int analogVal = 0;
int adcVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, INPUT); //Digital pin 13 is set to input mode
}

void loop() {
  int digitalVal = digitalRead(digitalPin);  //Read digital signal;
  int adcVal = analogRead(PIN_ANALOG_IN);
  int dacVal = map(adcVal, 0, 4095, 0, 255);
  double voltage = adcVal / 4095.0 * 3.3;
  Serial.printf("digitalVal: %d, \t ADC Val: %d, \t DAC Val: %d, \t Voltage: %.2fV\n",digitalVal, adcVal, dacVal, voltage);
  if (digitalVal == 1) {
    Serial.println("  Normal");
  }
  else {
    Serial.println("  Exceeding");
  }
  delay(5000); //Delay time 100 ms
}
