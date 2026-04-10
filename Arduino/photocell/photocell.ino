int ledPin = 9;
int photocellPin = A0;
int photocellReading;
int ledBrightness;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(photocellPin, INPUT);
}

void loop(){
  photocellReading = 1023 - analogRead(photocellPin);
  Serial.print("Photocell reading: ");
  Serial.println(analogRead(photocellPin));
  ledBrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);
  delay(100);
}