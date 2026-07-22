#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

//==WiFi credentials==
const char *ssid = u8"Azuan";
const char *pass = u8"Terengganu@11";

//==MQTT credentials==
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi();
void connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);

void setup()
{
    Serial.begin(115200);
    delay(100);

    Serial.println("===MQTT Test===");

    connectWiFi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    connectMQTT();

    // Publish message
    client.publish("mqtt/test", "Hello from esp32!");
    Serial.println("Message published");

    // Subscribe to a topic
    client.subscribe("mqtt/commands");
    Serial.println("Subscribed to mqtt/commands");
}

void loop()
{
    if (!client.connected())
    {
        connectMQTT();
    }

    client.loop();
}

void connectWiFi()
{
    WiFi.mode(WIFI_STA);
    delay(10);
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" Success");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void connectMQTT()
{
    Serial.print("Connecting to MQTT");
    while (!client.connected())
    {
        client.connect("ESP32_Client");
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" SUCCESS");
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message received on topic: ");
    Serial.println(topic);

    Serial.print("Payload: ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}