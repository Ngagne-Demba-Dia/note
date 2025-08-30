//
const int led=3;
const int photor=A5;

//int etatpoussoir= 1;
void setup()
{
  //Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lecture LDR demaree...");
}

void loop()
{
  int LDRvalue=analogRead(photor);
  Serial.print("valeur LDR :");
  Serial.print(LDRvalue);
  Serial.print("|");
   
  int position=map(LDRvalue,0,1023,0,50);
  for(int i=0;i<50;i++){
    if(i==position){
      Serial.print("*");
    }else{
      Serial.print("");
    }}
  Serial.println(" ");
  if(LDRvalue<500){
    digitalWrite(led,HIGH);
    Serial.println("LED : ON");
  }else{
    digitalWrite(led,LOW);
     }
}
