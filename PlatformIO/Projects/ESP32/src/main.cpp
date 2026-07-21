#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDR 8
#define ANSWERSIZE 5
String answer = "Hello";
String receivedData = "";

volatile bool dataReceived = false;
void requestEvent();
void receiveEvent(int howMany);

void setup()
{
    pinMode(21, INPUT_PULLUP);
    pinMode(22, INPUT_PULLUP);

    Wire.begin((uint8_t)SLAVE_ADDR, 21, 22, 100000);

    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);

    Serial.begin(9600);
    Serial.println("I2C Slave Demo");
}

void requestEvent()
{
    byte response[ANSWERSIZE];

    for (byte i = 0; i < ANSWERSIZE; i++)
    {
        response[i] = (byte)answer.charAt(i);
    }

    Wire.write(response, ANSWERSIZE);
}

void receiveEvent(int howMany)
{
    while (Wire.available())
    {
        char c = Wire.read();
        receivedData += c;
    }

    dataReceived = true;
}

void loop()
{
    if (dataReceived)
    {
        Serial.println("Data received from Master device");
        Serial.println(receivedData);
        dataReceived = false;
    }

    delay(50);
}