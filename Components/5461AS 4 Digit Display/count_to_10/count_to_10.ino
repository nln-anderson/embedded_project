// ---- Segment-to-pin mapping (confirmed) ----
//    _a_
//   f   b
//    _g_
//   e   c
//    _d_
const int PIN_A = 11;
const int PIN_B = 7;
const int PIN_C = 4;
const int PIN_D = 2;
const int PIN_E = 1;
const int PIN_F = 10;
const int PIN_G = 5;

const int segmentPins[7] = {PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G};
const int numPins = 7;

// Which segments are ON for each digit 0-9, in order a,b,c,d,e,f,g
const bool digitPatterns[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}, // 9
};

void setup(){
  for (int i = 0; i < numPins; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
}

void clearPins(){
  for (int i = 0; i < numPins; i++){
    digitalWrite(segmentPins[i], LOW);
  }
}

void showDigit(int digit){
  if (digit < 0 || digit > 9) return; // guard against bad input
  clearPins();
  for (int i = 0; i < numPins; i++){
    digitalWrite(segmentPins[i], digitPatterns[digit][i] ? HIGH : LOW);
  }
}

void loop(){
  for (int digit = 0; digit <= 9; digit++){
    showDigit(digit);
    delay(1000); // one second per digit — adjust as you like
  }
}