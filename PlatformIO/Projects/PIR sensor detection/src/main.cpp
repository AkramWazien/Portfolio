#include <Arduino.h>

#define PIR_PIN 2
#define TRIG_PIN 3
#define ECHO_PIN 4
#define LED_PIN A0

void setup()
{
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  delay(1000);
  int motionstate1 = digitalRead(PIR_PIN);
  delay(1000);
  int motionstate2 = digitalRead(PIR_PIN);
  delay(1000);
  int motionstate3 = digitalRead(PIR_PIN);
  // Serial.println(motionstate);
  if (motionstate1 == 1 || motionstate2 == 1 || motionstate3 == 1)
  {
    Serial.println("Motion detected");
    // digitalWrite(LED_PIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_PIN, LOW);
    Serial.println("Motion detected");
    Serial.println("Calculating distance.....");
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
  }

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 150)
  {
    int brightness = map(distance, 0, 150, 255, 0);
    brightness = constrain(brightness, 0, 255);
    analogWrite(LED_PIN, brightness);
  }

  delay(100);
}

// if (motionstate == HIGH)
// {
//   Serial.println("Motion detected");
//   Serial.println("Calculating distance.....");
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);
// }

// long duration = pulseIn(ECHO_PIN, HIGH);
// int distance = duration * 0.034 / 2;

// Serial.print("Distance: ");
// Serial.print(distance);
// Serial.println(" cm");

// if (distance < 150)
// {
//   int brightness = map(distance, 0, 150, 255, 0);
//   brightness = constrain(brightness, 0, 255);
//   analogWrite(LED_PIN, brightness);
// }

// delay(100);
// }