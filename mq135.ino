int sensorValue;
void setup(){
Serial.begin(9600);                            // sets the serial port to 9600
 }
void loop(){
sensorValue = analogRead(42);       // read analog input pin 0
Serial.print("AirQua=");
Serial.print(sensorValue);               // prints the value read
Serial.println(" PPM");
delay(1000);
}
