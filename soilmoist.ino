byte humidity_sensor_pin = A0;
byte humidity_sensor_vcc = 6;
int soilmoist;
void setup() {
  // Init the humidity sensor board
  pinMode(humidity_sensor_vcc, OUTPUT);
  digitalWrite(humidity_sensor_vcc, LOW);
  Serial.begin(9600);
}

int read_humidity_sensor() {
  digitalWrite(humidity_sensor_vcc, HIGH);
  delay(100);
  int value = analogRead(humidity_sensor_pin);
  digitalWrite(humidity_sensor_vcc, LOW);
  return 1023 - value;
}

void loop() {
  int i;
  Serial.print("Humidity Level (0-1023): ");
  for(i=1;i<=20;i++)
  {
  soilmoist += read_humidity_sensor();
  delay(100);
  }
  soilmoist=soilmoist/20;
  Serial.println(soilmoist); 
  delay(1000);
}
