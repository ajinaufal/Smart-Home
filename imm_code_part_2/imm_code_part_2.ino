int hujan;
int sensorlampu = 0;
int nRainVal;
boolean bIsRaining = false;
//WidgetLED led1(V6);
#include "DHT.h"
#define DHTTYPE DHT11

int sensorldr = A0;
#define BLYNK_PRINT Serial
#define relay1 D0
#define relay2 D1
#define relay3 D2
#define relay4 D3
#define relay5 D4
#define relay6 D5
#define dinamo D6
int nRainDigitalIn = D7;
#define DHTPIN D8

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
DHT dht(DHTPIN, DHTTYPE);
WidgetLCD lcd(V5);

char auth[] = "Z6klULLRx2S4rGd4jp34tamvZYsstbDz";
char ssid[] = "lixabet";
char pass[] = "datealive123";

unsigned long interval=300;
unsigned long interval1=300;
unsigned long previousMillis=0;

int relayv0;
int relayv1;
int relayv2;
int relayv3;
int relayv4;
int relayv5;
int dinamo1;
int counter;
int hasil;
String strRaining;

BLYNK_WRITE(V0){
  relayv0 = param.asInt();
  if (relayv0 == 1){ 
    digitalWrite(relay1, HIGH);
    Serial.println("Lampu Ruang Kerja On ");
  }else{
    digitalWrite(relay1, LOW);
    Serial.println("Lampu Ruang Kerja Off ");
  }
}

BLYNK_WRITE(V1){
  relayv1 = param.asInt();
  if (relayv1 == 1){ 
    digitalWrite(relay2, HIGH);
    Serial.println("Lampu Ruang Tamu On ");
  }else{
    digitalWrite(relay2, LOW);
    Serial.println("Lampu Ruang Tamu Off ");
  }
}

BLYNK_WRITE(V2){
  relayv2 = param.asInt();
  if (relayv2 == 1){ 
    digitalWrite(relay3, HIGH);
    Serial.println("Lampu Ruang Kamar Utama On ");
  }else{
    digitalWrite(relay3, LOW);
    Serial.println("Lampu Ruang Kamar Utama Off ");
  }
}

BLYNK_WRITE(V3){
  relayv3 = param.asInt();
  if (relayv3 == 1){ 
    digitalWrite(relay4, HIGH);
    Serial.println("Lampu Ruang Kamar Anak On ");
  }else{
    digitalWrite(relay4, LOW);
    Serial.println("Lampu Ruang Kamar Anak Off ");
  }
}

BLYNK_WRITE(V10){
  relayv4 = param.asInt();
  if (relayv4 == 1){ 
    digitalWrite(relay5, HIGH);
    Serial.println("Lampu Ruang Keluarga On ");
  }else{
    digitalWrite(relay5, LOW);
    Serial.println("Lampu Ruang Keluarga Off ");
  }
}

BLYNK_WRITE(V4){
  relayv5 = param.asInt();
  if (relayv5 == 1){ 
    digitalWrite(relay6, HIGH);
    Serial.println("AC Rumah On");
  }else{
    digitalWrite(relay6, LOW);
    Serial.println("AC Rumah Off");
  }
}

BLYNK_WRITE(V9){
  counter = param.asInt();
  /*if (counter == 1){ 
    Serial.println("Jemuran On");
    digitalWrite(dinamo, HIGH);
  }else{
    Serial.println("Jemuran Off");
    digitalWrite(dinamo, LOW);
  }*/
}

BLYNK_WRITE(V11){
  dinamo1 = param.asInt();
  if (dinamo1 == 1){ 
    Serial.println("Jemuran On");
    analogWrite(dinamo, 800);
    delay(600);
    analogWrite(D6, 0);
    Blynk.virtualWrite(V11, LOW);
  }else{
    Serial.println("Jemuran Off");
    analogWrite(D6, 0);
  }
}

void setup() {
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
pinMode(relay5, OUTPUT);
pinMode(relay6, OUTPUT);
pinMode(dinamo, OUTPUT);
dht.begin();
lcd.clear();
hujan = 0;

}

void loop() {
  
 unsigned long currentMillis = millis();
 if ((unsigned long)(currentMillis - previousMillis)>= interval){
    sensorlampu = analogRead(sensorldr);
    bIsRaining = !(digitalRead(nRainDigitalIn));
    float t = dht.readTemperature();
 }
 if ((unsigned long)(currentMillis - previousMillis)>= interval){
    Blynk.virtualWrite(V7,sensorlampu);
    Blynk.virtualWrite(V8, dht.readTemperature());
    /*if(bIsRaining){
      strRaining = "yes";
      Serial.println(strRaining);
      
    }
    else{
      strRaining = "no";
      Serial.println(strRaining);
      
    }*/
    previousMillis = millis();
 }
 if (counter == 1){
    //lampu
    if (sensorlampu <= 140){
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      Serial.println("Lampu Nyala");
      Blynk.virtualWrite(V0, HIGH);
      Blynk.virtualWrite(V1, HIGH);
      Blynk.virtualWrite(V2, HIGH);
      Blynk.virtualWrite(V3, HIGH);
      Blynk.virtualWrite(V10, HIGH);
      if (hujan == 0){
        Serial.println("Jemuran On");
        analogWrite(dinamo, 800);
        Blynk.virtualWrite(V11, HIGH);
        delay(600);
        analogWrite(D6, 0);
        Blynk.virtualWrite(V11, LOW);
        hujan = 1;
      }
    }else{
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, LOW);
      digitalWrite(relay5, LOW);
      Blynk.virtualWrite(V0, LOW);
      Blynk.virtualWrite(V1, LOW);
      Blynk.virtualWrite(V2, LOW);
      Blynk.virtualWrite(V3, LOW);
      Blynk.virtualWrite(V10, LOW);
      Serial.println("Lampu Mati");
    }
    //jemuran
    if(bIsRaining){
      strRaining = "yes";
      Serial.println(strRaining);
      lcd.print(0, 0, "Cuaca : hujan");
      if (hujan == 0){
        Serial.println("Jemuran On");
        analogWrite(dinamo, 800);
        Blynk.virtualWrite(V11, HIGH);
        delay(600);
        analogWrite(D6, 0);
        Blynk.virtualWrite(V11, LOW);
        hujan = 1;
        
      }
      /*digitalWrite(dinamo, HIGH);
      Serial.println("Jemuran Rumah On");
      Blynk.virtualWrite(V11, HIGH);
      analogWrite(dinamo, 100);
      lcd.print(0, 0, "Cuaca : Hujan");
      */
    }
    else{
      strRaining = "no";
      Serial.println(strRaining);
      //digitalWrite(dinamo, LOW);
      lcd.print(0, 0, "Cuaca : cerah");
      analogWrite(dinamo, 0);
      Serial.println("Jemuran Rumah Off");
      Blynk.virtualWrite(V11, LOW);
      
      hujan = 0;
    }
    
    //kipas angin
    if(dht.readTemperature() >= 30){
      digitalWrite(relay6, HIGH);
      Serial.println("AC Rumah On");
      Blynk.virtualWrite(V4, HIGH);
    }else{
      digitalWrite(relay6, LOW);
      Blynk.virtualWrite(V4, LOW);
      Serial.println("AC Rumah Off");
    }
  }
  
  
Blynk.run();
}
