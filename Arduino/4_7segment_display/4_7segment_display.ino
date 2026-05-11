#include <RtcDS1302.h>
#include <ThreeWire.h>

const int segmentPins[7] = {11, 10, 9, 8, 7, 6, 5};
const int digitPatterns[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}  // 9
};
int num = 0;
int D1Pin = 3;
int D2Pin = 2;
int D3Pin = 22;
int D4Pin = 23;
int dpPin = 4;
int buttonPin = 49;
int buttonPin1 = 48;
int buttonPin2 = 47;
int buttonPin3 = 46;
int buzzerPin = 45;
int mode = 0;
int previous2State = 0;
int previous1State = 0;
int previous3State = 0;
int MinTens = 0;
int MinOnes = 0;
int SecTens = 0;
int SecOnes = 0;
int place = 1;

ThreeWire myWire(51, 50, 52);
RtcDS1302<ThreeWire> Rtc(myWire);
char pin[1];

void setup() {
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(currentTime);
  pinMode(D1Pin, OUTPUT);
  pinMode(D2Pin, OUTPUT);
  pinMode(D3Pin, OUTPUT);
  pinMode(D4Pin, OUTPUT);
  pinMode(dpPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buzzerPin, OUTPUT);
  for(int count = 0; count < 7; count++) {
    pinMode(segmentPins[count], OUTPUT);
  }
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  //Rtc.SetDateTime(compiled);
  Rtc.SetIsRunning(true);
}

void display(int num, int number) {
  switch(number){
    case 1:digitalWrite(D1Pin, HIGH); break;
    case 2:digitalWrite(D2Pin, HIGH); break;
    case 3:digitalWrite(D3Pin, HIGH); break;
    case 4:digitalWrite(D4Pin, HIGH); break;
  }
  digitalWrite(dpPin, HIGH);
  if(number == 2) digitalWrite(dpPin, LOW);  
  for(int segment = 0; segment < 7; segment++) {
    digitalWrite(segmentPins[segment], digitPatterns[num][segment]);
  }
  delay(3);
  switch(number){
    case 1:digitalWrite(D1Pin, LOW); break;
    case 2:digitalWrite(D2Pin, LOW); break;
    case 3:digitalWrite(D3Pin, LOW); break;
    case 4:digitalWrite(D4Pin, LOW); break;
  }
}

void runClock() {
  RtcDateTime now = Rtc.GetDateTime();
  int minutes = now.Minute();

  int MinTens = minutes / 10;
  int MinOnes = minutes % 10;

  display(MinTens, 3);
  display(MinOnes, 4);

  int hour = now.Hour();
  int HourTens = hour / 10;
  int HourOnes = hour % 10;

  display(HourTens, 1);
  display(HourOnes, 2);
}

void runTimer() {
  int button2Input = digitalRead(buttonPin2);
  int button1Input = digitalRead(buttonPin1);
  int button3Input = digitalRead(buttonPin3);

  if (button2Input == 1 && button2Input != previous2State) {
    place += 1;
    if (place > 4) {
      place = 1;
    }
  }
  previous2State = button2Input;

  if (button1Input == 1 && button1Input != previous1State) {
    if (place == 1) {
    MinTens += 1;
    if(MinTens > 9) {
      MinTens = 0;
    }
  } else if (place == 2){
    MinOnes += 1;
    if(MinOnes > 9) {
      MinOnes = 0;
    }
  } else if (place == 3){
    SecTens += 1;
    if(SecTens > 6) {
      SecTens = 0;
    }
  } else if (place == 4){
    SecOnes += 1;
    if (SecTens == 6) {
      SecOnes = 0;
    }
    if (SecOnes > 9) {
      SecOnes = 0;
    }
  }
  if (SecTens == 6) {
      SecOnes = 0;
    }
  }
  previous1State = button1Input;

  if (button3Input == 1 && button3Input != previous3State) {
    unsigned long buttonPressed = millis();
    while(SecOnes != 0 || SecTens != 0 || MinOnes != 0 || MinTens != 0) {
      display(MinTens, 1);
      display(MinOnes, 2);
      display(SecTens, 3);
      display(SecOnes, 4);
      if (millis() - buttonPressed >= 1000) {
        buttonPressed = millis();
        SecOnes -= 1;
        if (SecOnes < 0) {
          SecOnes = 9;
          SecTens -= 1;
        }
      }
    }
    if(SecOnes == 0 && SecTens == 0 && MinOnes == 0 && MinTens == 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(5000);
      digitalWrite(buzzerPin, LOW);
    }
  }
  previous3State = button3Input;

  display(MinTens, 1);
  display(MinOnes, 2);
  display(SecTens, 3);
  display(SecOnes, 4);
}

void loop() {
  int buttonInput = digitalRead(buttonPin);
  if (buttonInput == 1 && mode == 0){
    mode = 1;
    delay(1000);
  }else if(buttonInput == 1 && mode == 1) {
    mode = 0;
    delay(1000);
  }
  switch (mode) {
    case 0:runClock();break;
    case 1:runTimer();break;
  }
}