#include <Arduino.h>
#include <VarSpeedServo.h>

int joystick1 = A0;
int joystick2 = A1;
VarSpeedServo servoKnee1, servoKnee2, servoLeg1, servoLeg2;

void setup() {
  pinMode(joystick1, INPUT);
  pinMode(joystick2, INPUT);
  servoKnee1.attach(A2);
  servoKnee2.attach(A3);
  servoLeg1.attach(A4);
  servoLeg2.attach(A5);
}

void loop() {
  int joystickValue1 = analogRead(joystick1);
  int joystickValue2 = analogRead(joystick2);
  int rLegvalue = map(joystickValue1, 0, 1023, 0, 180);
  int rKneevalue = map(joystickValue2, 0, 1023, 0, 180);
  int lLegvalue = map(joystickValue1, 0, 1023, 180, 0);
  int lKneevalue = map(joystickValue2, 0, 1023, 180, 0);
  servoLeg1.write(rLegvalue, 80);
  servoLeg2.write(lLegvalue, 80);
  servoKnee1.write(rKneevalue, 150);
  servoKnee2.write(lKneevalue, 150);
  delay(100);
}
