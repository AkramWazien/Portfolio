#include <Arduino.h>
#include <Ds1302.h>

Ds1302 rtc(4, 2, 3);
int lastDay;
rtc.init();

void setup(){
    Serial.begin(9600);
}

void loop(){
    static unsigned long lastMillis;
    if(millis() - lastMillis >= 1000){
        lastMillis = millis();

        Ds1302::DateTime dt;
        rtc.getDateTime(&dt);

        if(dt.day != lastDay){
            lastDay = dt.day;
            Serial.println("--------Date---------");
            Serial.print(dt.day);
            Serial.print("/");
            Serial.print(dt.month);
            Serial.print("/");
            Serial.print(dt.year);
        }
        Serial.print("Time: ");
        Serial.print(dt.hour);
        Serial.print(":");
        Serial.print(dt.minute);
        Serial.print(":");
        Serial.print(dt.second);
      }
}