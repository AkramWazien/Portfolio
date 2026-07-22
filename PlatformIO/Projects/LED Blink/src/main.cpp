#include <Arduino.h>
#include <WiFi.h>
#include <ESP32_Servo.h>

const char *ssid = "ESP32";
const char *password = "AKRAMESP32";
WiFiServer server(80);
Servo myServo;
#define servoPin 26
String header;

void setup()
{
  Serial.begin(115200);
  myServo.attach(servoPin, 500, 2400);

  Serial.println("Setting up Soft AP.....");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 1, 0, 1);

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New client connected");
    String currentline = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        header += c;
        if (c == '\n')
        {
          if (currentline.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /servo/0") >= 0)
            {
              Serial.println("Servo to 0 degrees");
              myServo.write(0);
            }
            else if (header.indexOf("GET /servo/90") >= 0)
            {
              Serial.println("Servo to 90 degrees");
              myServo.write(90);
            }
            else if (header.indexOf("GET /servo/180") >= 0)
            {
              Serial.println("Servo to 180 degrees");
              myServo.write(180);
            }

            // Generate the HTML control web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>My Web Server</title>");
            client.println("<style>html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #042da9; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");

            client.println("<body><h1>ESP32 SAP Web Server</h1>");
            client.println("<p>Control your servo via Wi-Fi</p>");

            client.println("<p><a href = \"/servo/0\"><button class=\"button\">0 degrees</button></a></p>");
            client.println("<p><a href = \"/servo/90\"><button class=\"button\">90 degrees</button></a></p>");
            client.println("<p><a href = \"/servo/180\"><button class=\"button\">180 degrees</button></a></p>");
            client.println("</body></html>");

            client.println();
            break;
          }
          else
          {
            currentline = "";
          }
        }
        else if (c != '\r')
        {
          currentline += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
  }
}
