const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Digit patterns for 0-9 on a common-cathode 7-segment display
// Order of segments: a b c d e f g
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

void setup() {
  // Set all segment pins as OUTPUT
  for(int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void displayDigit(int digit) {
  if(digit < 0 || digit > 9) return; // Only digits 0-9 supported
  for(int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digitPatterns[digit][i]);
  }
}

void loop() {
  // Example: Display digits 0-9 with a 1-second delay
  for(int digit = 9; digit >= 0; digit--) {
    displayDigit(digit);
    delay(1000); // Wait 1 second before next digit
  }
}