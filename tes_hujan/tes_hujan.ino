int nRainIn = A0;
int nRainDigitalIn = D6;
int nRainVal;
boolean bIsRaining = false;
String strRaining;


void setup() {
  Serial.begin(9600);
  pinMode(D6,INPUT);
}
void loop() {
  //nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }
  
  Serial.print("Raining?: ");
  Serial.println(strRaining);  
  //Serial.print("\t Moisture Level: ");
  //Serial.println(nRainVal);
  
  delay(200);
}
