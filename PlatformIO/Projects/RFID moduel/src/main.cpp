#include <Arduino.h>
#include <VarSpeedServo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 49
#define SS_PIN 53
#define MOSI_PIN 51
#define MISO_PIN 50
#define SCK_PIN 52
#define SERVO_PIN 12
VarSpeedServo myServo;
MFRC522 rfid(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  myServo.attach(SERVO_PIN);
  myServo.write(0, 255);
}
void loop()
{
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;
  String tagUID = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    tagUID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tagUID.concat(String(rfid.uid.uidByte[i], HEX));
  }
  tagUID.toUpperCase();
  if (tagUID.substring(1) == "87 C9 69 05" || tagUID.substring(1) == "8C 8D 98 04")
  {
    myServo.write(90, 100);
    delay(100);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}