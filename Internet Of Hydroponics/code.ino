#include "UbidotsMicroESP8266.h"
#include "DHT.h"
#include "Servo.h" 
 
Servo myservo; 

#define DHTTYPE DHT11
#define DHTPIN D8
DHT dht(DHTPIN, DHTTYPE);

#define TOKEN "A1E-tGMSTAhWnlUWvQ7POWf8xKH0NfyAcV" 
#define AUTOID "5a61d206c03f97742d037901"
#define PUMP1 "5a61cf6ec03f97716d2f7a25"
#define PUMP2 "5a61cf78c03f9771e1153545"
#define SERVOID "5a61cf1dc03f9771e115352c"
#define ID_2 "5a617dedc03f971f8e2e294b" // Put your variable ID here
#define WIFISSID "prasad" // Put here your Wi-Fi SSID
#define PASSWORD "12345678" // Put here your Wi-Fi password

Ubidots client(TOKEN);
static int flag=0;
int pos=0;
//int p=0;
void setup(){
  myservo.attach(D6);
    dht.begin();
    pinMode(D6,OUTPUT);
    pinMode(D4,OUTPUT);
    pinMode(D5,OUTPUT);
     Serial.begin(9600);
    
    //client.wifiConnection(WIFISSID, PASSWORD);
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop(){
  int a= client.getValue(AUTOID);
 Serial.println(a);
 if(a==1){
    Serial.println("Automated");
    float t = dht.readTemperature();
    if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    Serial.print("Temperature: ");
  Serial.print(t);
    //client.add(ID_1, t);
    client.add(ID_2, t);
    client.sendAll(false);
   Serial.println(t);
   if((t>=26) && (flag==0)) {
      for(pos = 0; pos <= 180; pos += 1)  
  {                                  
    myservo.write(pos);              
    delay(15);                      
  } 
  Serial.println("Opened");
  flag=1;
 // delay(5000);
    }
    if((t<26) && (flag==1)){
        for(pos = 180; pos>=0; pos -=1)     
  {                                
    myservo.write(pos);              
    delay(15);                       
  } 
  Serial.println("Closed");
  flag=0;
        }
      //(5000);
    //PREVENTION DONE

      //CURE PART CODE
      else{
        int sensorValue = analogRead(A0);
        Serial.println(sensorValue);
        delay(2000);
        if(sensorValue==1024){
          Serial.println("No Algae");
          delay(2000);
          }
          else{
            Serial.println("Algae Determined");
            delay(2000);
            Serial.println("Pumping OUT");
            digitalWrite(D4,HIGH);
            delay(5000);
            for(int i=0;i<=10000;i++){
              }
             digitalWrite(D4,LOW);
             Serial.println("Pumping Done");
             Serial.println("Pumping In");
              digitalWrite(D5,HIGH);
              delay(5000);
              for(int i=0;i<=10000;i++){
              }
              digitalWrite(D5,LOW);
              Serial.println("Pumping in done!!!!!!!!");
            }
        
        }
      
 }
 else{
  int flag1=0;
  Serial.println(a);
  Serial.println("Manual");
  client.add(PUMP1, LOW);
  client.add(PUMP2, LOW);
  client.sendAll(false);
  delay(2000);
  int ser = client.getValue(SERVOID);
  if(ser==1){
    flag1=1;
    }
  if((ser==1) && (flag1==1)){
    for(pos = 0; pos <= 180; pos += 1)  
  {                                  
    myservo.write(pos);              
    delay(15);                      
  } 
  Serial.println("Opened");
  delay(3000);
    }
    else{
      for(pos = 180; pos>=0; pos -=1)     
  {                                
    myservo.write(pos);              
    delay(15);                       
  } 
  Serial.println("Closed");
      }
      //PUMP IN AND OUT
      int p1=client.getValue(PUMP1);
      if(p1==1){
        Serial.println("Pumping in");
        digitalWrite(D5,HIGH);
        delay(5000);
        }
        else{
          digitalWrite(D5,LOW);
          Serial.println("pumping in Turned off");
          delay(2000);
          }
          int p2=client.getValue(PUMP1);
          if(p2==1){
            Serial.println("Pumping out");
            digitalWrite(D4,HIGH);
            delay(5000);
            }
            else{
          digitalWrite(D4,LOW);
          Serial.println("pumping out Turned off");
          delay(2000);
          }
  }
}
