#include <Arduino.h>
#include <esp_sleep.h>

#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_0

int setTime = 10;

RTC_DATA_ATTR int count = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (reason == ESP_SLEEP_WAKEUP_EXT0)
  {
    count = 0;
    Serial.println("Button is pressed. Counter reset.");
  }
  else
  {
    Serial.println("Waking up!");
    count++;
    Serial.printf("Boot number %d\n", count);

    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);

    Serial.printf("Going to sleep for %d seconds...\n", setTime);
    delay(100);
  }

  esp_sleep_enable_timer_wakeup(setTime * 1000000);
  esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 0);

  esp_deep_sleep_start();
}

void loop()
{
}
