# Title: ESP32 SPIFFS

Date: 21-07-2026

This code is used to store log data using esp32 SPIFFS.h header file. It is also paired with the esp32_sleep.h header file to imitate a data logger that runs on low power in an oil rig. It sleeps for a few second and receive datas from multiple sensor. There is also an override button that immediately wake the logger up and log data. This data logger only store 5 recent data logs since it has small memory amount and there is no need for a lot of data.

From this project, I was able to integrate between two esp32 function that is sleep and spiffs. I may add a real sensor data in the future
