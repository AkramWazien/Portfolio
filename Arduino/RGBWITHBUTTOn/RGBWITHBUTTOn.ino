#define buttonA 5
#define buttonB 8
#define buttonC 9

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonA) == LOW){
    analogWrite(buttonA, 100);
  }
  if(digitalRead(buttonB) == LOW){
    analogWrite(buttonB, 50);
  }
  if(digitalRead(buttonC) == LOW){
    analogWrite(buttonC, 255);
  }
}
