#include <Arduino.h>
#include <esp_sleep.h>
#include <SPIFFS.h>

#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_0

int setTime = 10;

RTC_DATA_ATTR int bootCount = 0;

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // mount spiffs
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS mount failed");
        return;
    }

    Serial.println("SPIFFS mounted successfully");

    // log data
    bootCount++;
    float fakeTemp = 25.0 + random(-5, 5);
    float fakeHumid = 60.0 + random(-10, 10);

    File file = SPIFFS.open("/log.txt", FILE_APPEND);
    if (file)
    {
        file.printf("Boot #%d, Temp: #%.1f, Humid: #%.1f\n", bootCount, fakeTemp, fakeHumid);
        file.close();
        Serial.println("Data logged");
    }
    else
    {
        Serial.println("Failed to open file");
    }

    File readFile = SPIFFS.open("/log.txt", FILE_READ);

    if (readFile)
    {
        Serial.println("---Last 5 logs---");

        const int KEEP = 5;
        String lastlines[KEEP];
        int index = 0;
        int totalLines = 0;

        while (readFile.available())
        {
            String line = readFile.readStringUntil('\n');
            if (line.length() > 0)
            {
                lastlines[index % KEEP] = line;
                index++;
                totalLines++;
            }
        }
        readFile.close();

        int start = totalLines < KEEP ? 0 : totalLines % KEEP;
        int count = totalLines < KEEP ? totalLines : KEEP;
        for (int i = 0; i < count; i++)
        {
            Serial.println(lastlines[(start + i) % KEEP]);
        }
    }

    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);

    Serial.printf("Going to sleep for %d seconds...", setTime);
    delay(100);

    esp_sleep_enable_timer_wakeup(setTime * 1000000);
    esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 0);

    esp_deep_sleep_start();
}

void loop()
{
}
