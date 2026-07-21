Title: ESP32 deep sleep

Date: 20-07-2026

This code utilises esp32_sleep.h header file and can be used to turn off the esp32 chip and turn it on again after a few second. There is also an external interrupt button that allows the esp32 to wake up immediately. This is used to prevent esp32 from using too much power and allows it to run on a single battery for longer period. 

From this project, I learnt a few way to wake up the chip which is 1. timer, 2. external0 which takes one input such as a button, and 3. external1 which takes more than one input and can be set to wake up the chip if one is met or if all of them are met.
