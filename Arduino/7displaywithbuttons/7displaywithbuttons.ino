const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};
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
int buttonPin1 = 9;
int buttonPin2 = 10;
int buttonPin3 = 11;
int buzzerPin = 12;
static int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void displayNumber(int count) {
  for(int num = 0; num < 7; num++){
  digitalWrite(segmentPins[num], digitPatterns[count][num]);
  }
}

void countDown(int count) {
  if(count == 0){
    displayNumber(count = 0);
  }else{
    for(int place = count; place--;) {
      displayNumber(place);
      if(place == 0) {
        digitalWrite(buzzerPin, HIGH);
        Serial.println("Buzzer sound");
        delay(5000);
        digitalWrite(buzzerPin, LOW);
      } 
      delay(1000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(buttonPin1);
  int sensorValue2 = digitalRead(buttonPin2);
  int sensorValue3 = digitalRead(buttonPin3);

  if(sensorValue == 0){
    count++;
    if(count > 9){
      count = count - 10;
    }
  }


  while(sensorValue == 0){
  delay(100);
  sensorValue = digitalRead(buttonPin1);
    }


  if(sensorValue2 == 0 and count != 0){
    count--;
  }


  while(sensorValue2 == 0){
  delay(100);
  sensorValue2 = digitalRead(buttonPin2);
  }

  displayNumber(count);


  if(sensorValue3 == 0){
    countDown(count);
  }
  delay(100);
}