#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDR 8
#define ANSWERSIZE 5

void setup()
{
    pinMode(20, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);

    Wire.begin();
    Wire.setClock(100000);

    Serial.begin(9600);
    delay(5000);
    Serial.println("I2C MASTER DEMO");
}

void loop()
{
    delay(1000);
    Serial.println("Write data to slave");

    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write("Data");
    byte error = Wire.endTransmission();

    if (error == 0)
    {
        Serial.println("Data sent successfully!");
    }
    else
    {
        Serial.print("Transmission failed! Error: ");
        switch (error)
        {
        case 1:
            Serial.println("Data too long to fit in transmit buffer");
            break;
        case 2:
            Serial.println("NACK received on address");
            break;
        case 3:
            Serial.println("NACK received on data");
            break;
        case 4:
            Serial.println("Other error");
            break;
        }
        return; // Skip the rest of this loop iteration
    }

    Serial.println("Receive data");

    delay(50);
    Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);
    String response = "";
    while (Wire.available())
    {
        char b = Wire.read();
        response += b;
    }

    Serial.println(response);
}