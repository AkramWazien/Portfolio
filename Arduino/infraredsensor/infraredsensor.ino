int infraredPin = A0;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(infraredPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float infraredReading = analogRead(infraredPin);
  float voltage = infraredReading * (5.0/1023.0);
  distance = 27.86 * pow(voltage, -1.15);
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
