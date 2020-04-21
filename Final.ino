#include<SoftwareSerial.h>
#include <dht.h>
#include <Wire.h>
SoftwareSerial Serial1(2,3); 
dht DHT;
#define DHT11_PIN 8
byte soilmoist_pin = A0;
byte temp_vcc = 6;
int soilmoist;
#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define sensorOut 9
int R,G,B = 0;
int sensorValue;
void setup() {
  pinMode(DHT11_PIN, INPUT);
  pinMode(temp_vcc, OUTPUT);
  digitalWrite(temp_vcc, LOW);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);

   // put your setup code here, to run once:
    // initialize serial communications and wait for port to open: 
   Serial1.begin(9600); 
  Serial.println("Sending SMS ");
  initModule("AT","OK",1000);
  initModule("ATE1","OK",1000);
  initModule("AT+CPIN?","READY",1000);  
  initModule("AT+CMGF=1","OK",1000);     
  initModule("AT+CNMI=2,2,0,0,0","OK",1000);  
  Serial.println("Initialized Successfully");
  Serial.println("Initialized");
  Serial.println("Successfully");
  delay(2000);
}

int read_humidity_sensor() {
  digitalWrite(temp_vcc, HIGH);
  delay(100);
  int value = analogRead(soilmoist_pin);
  digitalWrite(temp_vcc, LOW);
  return 1023-value;
}
void initModule(String cmd, char *res, int t)
{
  while(1)
  {
    Serial.println(cmd);
    Serial1.println(cmd);
    delay(1000);
    Serial.println(Serial1.available());
    while(Serial1.available()>0)
    {
       if(Serial1.find(res))
       {
        Serial.println(res);
        delay(t);
        return;
       }

       else
       {
        Serial.println("Error");
       }
    }
    delay(t);
  }
}
void loop() {
  //soil moisture
  int i;
  Serial.print("soil moisture level (0-1023): ");
  for(i=1;i<=20;i++)
  {
  soilmoist += read_humidity_sensor();
  delay(100);
  }
  soilmoist=soilmoist/20;
  Serial.println(soilmoist); 
  if(soilmoist<300)
  {
    Serial.print("The crop needs to be watered\n");
    Send1();
  }

  
  //temperature and humidity
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  double T=DHT.temperature;
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  if(T>30)
  {
    Serial.print("The temperature is beyond the range,turn on sprinklers\n");
    Send2();
  }
  //color sensor
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  R = pulseIn(sensorOut, LOW);
  Serial.print("R= ");
  Serial.print(R);
  Serial.print("  ");
  delay(100);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  G = pulseIn(sensorOut, LOW);
  Serial.print("G= ");
  Serial.print(G);
  Serial.print("  ");
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  B = pulseIn(sensorOut, LOW);
  Serial.print("B= ");
  Serial.print(B);
  Serial.println("  \n");
  if(R>=23&&R<=54)
  {
    if(G>=29&&G<=69)
    {
      if(B>=33&&B<=75)
      {
          Serial.print("Potato crop is ready to harvest\n\n");
          Send3();
         
      }
    }

  }
  else
      {
        Send4();
      }
  delay(1000);

   //gas sensor
   sensorValue = analogRead(A1);       // read analog input pin 0
   Serial.print("AirQua=");
   Serial.print(sensorValue);               // prints the value read
   Serial.println(" PPM");
   delay(200000);
}
void Send1()
{ 
   Serial1.println("AT");
   delay(500);
   serialPrint();
   Serial1.println("AT+CMGF=1");
   delay(500);
   serialPrint();
   Serial1.print("AT+CMGS=");
   Serial1.print('"');
   Serial1.print("9573226072");    //mobile no. for SMS alert
   Serial1.println('"');
   delay(500);
   serialPrint();
   delay(500);
   serialPrint();
   Serial1.print("The crop needs to be watered");
   Serial1.write(26);
   delay(2000);
   serialPrint();
}
void Send2()
{ 
   Serial1.println("AT");
   delay(500);
   serialPrint();
   Serial1.println("AT+CMGF=1");
   delay(500);
   serialPrint();
   Serial1.print("AT+CMGS=");
   Serial1.print('"');
   Serial1.print("9573226072");    //mobile no. for SMS alert
   Serial1.println('"');
   delay(500);
   serialPrint();
   delay(500);
   serialPrint();
   Serial1.print("The temperature is beyond the range,turn on sprinklers");
   Serial1.write(26);
   delay(2000);
   serialPrint();
}
void Send3()
{ 
   Serial1.println("AT");
   delay(500);
   serialPrint();
   Serial1.println("AT+CMGF=1");
   delay(500);
   serialPrint();
   Serial1.print("AT+CMGS=");
   Serial1.print('"');
   Serial1.print("9573226072");    //mobile no. for SMS alert
   Serial1.println('"');
   delay(500);
   serialPrint();
   delay(500);
   serialPrint();
   Serial1.print("Potato crop is ready to harvest");
   Serial1.write(26);
   delay(2000);
   serialPrint();
}
void Send4()
{ 
   Serial1.println("AT");
   delay(500);
   serialPrint();
   Serial1.println("AT+CMGF=1");
   delay(500);
   serialPrint();
   Serial1.print("AT+CMGS=");
   Serial1.print('"');
   Serial1.print("9573226072");    //mobile no. for SMS alert
   Serial1.println('"');
   delay(500);
   serialPrint();
   delay(500);
   serialPrint();
   Serial1.print("Potato crop is not ready to harvest");
   Serial1.write(26);
   delay(2000);
   serialPrint();
}
void serialPrint()
{
  while(Serial1.available()>0)
  {
    Serial.print(Serial1.read());
  }
}
