#define ldr A0
#include "dht.h"
#define dht_pin D0
#define hujan D1
#define relay1 D2
#define relay2 D3
#define relay3 D4
#define relay4 D5
#define relay5 D6
#define relay6 D7
#define dinamo D8
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";
dht DHT;
int ldrvalue = 0;
unsigned long interval=300;
unsigned long interval1=300;
unsigned long previousMillis=0;
int relayv0;
int relayv1;
int relayv2;
int relayv3;
int relayv4;
int relayv5;
int relayv6;
WidgetLCD lcd(V9)
WidgetLED led1(V6);

BLYNK_WRITE(V0){
  relayv0 = paramasInt();
  if (relayv0 == 1){ 
  }
}

BLYNK_WRITE(V1){
  relayv1 = paramasInt();
}

BLYNK_WRITE(V2){
  relayv2 = paramasInt();
}

BLYNK_WRITE(V3){
  relayv3 = paramasInt();
}

BLYNK_WRITE(V4){
  relayv4 = paramasInt();
}

BLYNK_WRITE(V5){
  relayv5 = paramasInt();
}

void setup() {
Serial.begin(9600);
delay(500);
Blynk.begin(auth, ssid, pass);
pinMode(hujan, INPUT);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
pinMode(relay5, OUTPUT);
pinMode(relay6, OUTPUT);
}

void loop() {
 lcd.print(0.0,"cuaca :");
 unsigned long currentMillis = millis();
 if ((unsigned long)(currentMillis - previousMillis)>= interval){
    ldrvalue = analogRead(ldr);
    int kondisi = digitalRead(hujan);
    DHT.read11(dht_pin);
    previousMillis = millis();
 }
 if ((unsigned long)(currentMillis - previousMillis)>= interval){
    Serial.print("suhu : ");
    Serial.print(DHT.temperature);
    Serial.println("C");
    Serial.print("lampu : ");
    Serial.println(ldrvalue);
    Blynk.virtualWrite(V7, ldrvalue);
    Blynk.virtualWrite(V8, DHT.temperature);
    previousMillis = millis();
 }
 if (DHT.temperature >= 28){
    digitalWrite(relay6,HIGH);
    led1.on();
 }else{
    digitalWrite(relay6,LOW);
    led1.off();
 }
 if (ldrvalue <=500){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
    digitalWrite(relay5, LOW);
 }else{
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    digitalWrite(relay5, HIGH);
 }
 if (kondisi == HIGH){
    digitalWrite(dinamo, HIGH);
    lcd.print(8,2,"Hujan");
 }
 if ((ldrvalue >=450)&&(kondisi == LOW)) {
    digitalWrite(LED, LOW);
    lcd.print(8,2,"cerah");
 }
 if ((ldrvalue >=450)&&(ldrvalue <=500 )){
    lcd.print(8,2,"Berawan");
 }
}
