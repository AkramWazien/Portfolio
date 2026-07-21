#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

#define CLK_PIN 7
#define DAT_PIN 6
#define RST_PIN 5
#define BUTTON1 4
#define BUTTON2 3
#define BUZZER_PIN 2

ThreeWire myWire(DAT_PIN, CLK_PIN, RST_PIN);
RtcDS1302<ThreeWire> RTC(myWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RtcDateTime timeSet(2026, 7, 18, 0, 20, 0);
uint64_t seconds = 20 * 60;

int mode = 0;
bool timerRunning = 0;
bool buzzerRunning = 0;

static unsigned long lastButtonPressTime = 0;
unsigned long prevClockMillis = 0;
unsigned long buzzerTime = 0;

typedef enum
{
  CLOCK = 0,
  TIMER = 1
} MODE;

void clock();
void timer();
int handleButtonPress(int type);

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  RTC.Begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DS1302 I2C LCD");
  lcd.setCursor(0, 1);
  lcd.print("Module");
  delay(1000);
  lcd.clear();
}

void loop()
{
  handleButtonPress(1);

  if (mode == 0)
  {
    clock();
  }
  else if (mode == 1)
  {
    timer();
  }
}

int handleButtonPress(int type)
{
  if (type == 1)
  {
    int reading = digitalRead(BUTTON1);
    const unsigned long interval = 200;

    if (reading == LOW && (millis() - lastButtonPressTime) > interval)
    {
      lastButtonPressTime = millis();
      lcd.clear();
      mode = !mode;

      lcd.setCursor(0, 0);
      lcd.print(mode == 0 ? "Clock mode    " : "Timer mode    ");
      delay(1000);
      lcd.clear();
      return 0;
    }
  }
  else if (type == 2)
  {
    int reading = digitalRead(BUTTON2);
    const unsigned long interval = 200;

    if (reading == LOW && (millis() - lastButtonPressTime) > interval)
    {
      lastButtonPressTime = millis();
      return 1;
    }
  }

  return 0;
}

void clock()
{
  if (millis() - prevClockMillis >= 1000)
  {
    prevClockMillis += 1000;
    RtcDateTime dateTime = RTC.GetDateTime();

    lcd.setCursor(0, 0);
    lcd.print("Date: ");
    if (dateTime.Day() < 10)
    {
      lcd.print("0");
    }
    lcd.print(dateTime.Day());
    lcd.print("/");
    if (dateTime.Month() < 10)
    {
      lcd.print("0");
    }
    lcd.print(dateTime.Month());
    lcd.print("/");
    lcd.print(dateTime.Year());
    lcd.print("      ");

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    if (dateTime.Hour() < 10)
    {
      lcd.print("0");
    }
    lcd.print(dateTime.Hour());
    lcd.print(":");
    if (dateTime.Minute() < 10)
    {
      lcd.print("0");
    }
    lcd.print(dateTime.Minute());
    lcd.print(":");
    if (dateTime.Second() < 10)
    {
      lcd.print("0");
    }
    lcd.print(dateTime.Second());
    lcd.print("      ");
  }
}

void timer()
{
  static unsigned long prevMillis = 0;

  if (!timerRunning)
  {
    prevMillis = millis();
  }
  uint8_t minuteTime = seconds / 60;
  uint8_t secondTime = seconds % 60;

  lcd.setCursor(5, 0);
  lcd.print("Timer");
  lcd.setCursor(5, 1);
  lcd.print(minuteTime);
  lcd.print(":");
  secondTime < 10 ? lcd.print("0") : lcd.print("");
  lcd.print(secondTime);
  lcd.print("     ");

  if (handleButtonPress(2) == 1)
  {
    timerRunning = !timerRunning;
  }

  if (timerRunning == 1)
  {
    if (seconds == 0)
    {
      buzzerTime = millis();
      digitalWrite(BUZZER_PIN, HIGH);
      timerRunning = 0;
      buzzerRunning = 1;
      seconds = 20 * 60;
    }
    if ((millis() - prevMillis) >= 1000)
    {
      prevMillis += 1000;
      seconds--;
    }
  }

  if (buzzerRunning == 1 && (millis() - buzzerTime) >= 10000)
  {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerRunning = 0;
  }
}