#define blue 3
#define green 5
#define red 6


void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(red, 0);
  analogWrite(blue, 0);
  analogWrite(green, 10);
  delay(500);
  analogWrite(blue, 255);
  analogWrite(green, 255);
  delay(500);
  analogWrite(red, 255);
  delay(500);
}
