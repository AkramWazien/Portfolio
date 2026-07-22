#include <Arduino.h>
#include <ESP32Servo.h>
#include <ServoEasing.hpp>

Servo servo1;
Servo servo2;
#define servo1Pin 25
#define servo2Pin 26
#define x_axis 32
#define y_axis 33

int readStabilizedJoystick(int pin)
{
  long sum = 0;
  int samples = 16; // Take 16 readings to smooth out the noise

  for (int i = 0; i < samples; i++)
  {
    sum += analogRead(pin);
    delayMicroseconds(50); // Small pause between readings
  }

  return sum / samples; // Return the filtered average
}

void setup()
{
  Serial.begin(115200);
  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);
}

void loop()
{
  uint8_t x_value = readStabilizedJoystick(x_axis);
  x_value = map(x_value, 0, 255, 0, 180);
  delay(2);
  readStabilizedJoystick(y_axis);
  delay(2);
  uint8_t y_value = readStabilizedJoystick(y_axis);
  y_value = map(y_value, 0, 255, 0, 180);
  Serial.print("X value: ");
  Serial.println(x_value);
  Serial.print("Y value: ");
  Serial.println(y_value);
  delay(1000);
}