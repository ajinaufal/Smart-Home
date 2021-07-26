  // put your setup code here, to run once:
#define relay1 D0
#define relay2 D1
#define relay3 D2
#define relay4 D3
#define relay5 D4
#define relay6 D5
#define dinamo D6
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
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
int relayv6;
BLYNK_WRITE(V0){
  relayv0 = param.asInt();
  if (relayv0 == 1){ 
    digitalWrite(relay1, HIGH);
  }else{
    digitalWrite(relay1, LOW);
  }
}

BLYNK_WRITE(V1){
  relayv1 = param.asInt();
  if (relayv1 == 1){ 
    digitalWrite(relay2, HIGH);
  }else{
    digitalWrite(relay2, LOW);
  }
}

BLYNK_WRITE(V2){
  relayv2 = param.asInt();
  if (relayv2 == 1){ 
    digitalWrite(relay3, HIGH);
  }else{
    digitalWrite(relay3, LOW);
  }
}

BLYNK_WRITE(V3){
  relayv3 = param.asInt();
  if (relayv3 == 1){ 
    digitalWrite(relay4, HIGH);
  }else{
    digitalWrite(relay4, LOW);
  }
}

BLYNK_WRITE(V4){
  relayv4 = param.asInt();
  if (relayv4 == 1){ 
    digitalWrite(relay5, HIGH);
  }else{
    digitalWrite(relay5, LOW);
  }
}

BLYNK_WRITE(V10){
  relayv5 = param.asInt();
  if (relayv5 == 1){ 
    digitalWrite(relay6, HIGH);
  }else{
    digitalWrite(relay6, LOW);
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
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
