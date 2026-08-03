#include <SevSeg.h>

SevSeg sevseg;
#define MAX_NUMBER_STRINGS 12
#define MAX_STRING_SIZE 8
char testStrings[MAX_NUMBER_STRINGS][MAX_STRING_SIZE];

#define PATTERN_CHANGE_TIME 1000
unsigned long timer = millis() - PATTERN_CHANGE_TIME;
byte testStringsPos = 0;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {12,9,8,6};
  byte segmentPins[] = {11,7,4,2,1,10,5,3};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
    updateWithDelays, leadingZeros, disableDecPoint);
    sevseg.setBrightness(50);
  // Adds set of test strings with periods in various places
  strcpy(testStrings[0], "A..BC.");
  strcpy(testStrings[1], "....");
  strcpy(testStrings[2], ".   ");
  strcpy(testStrings[3], " .  ");
  strcpy(testStrings[4], "  . ");
  strcpy(testStrings[5], "   .");
  strcpy(testStrings[6], ".ABC");
  strcpy(testStrings[7], "A.BCD");
  strcpy(testStrings[8], "A.B.CD");
  strcpy(testStrings[9], "A.B.C.D");
  strcpy(testStrings[10], "A.B.C.D.");
  strcpy(testStrings[11], ". . . .");
}

void loop() {

  // Cycle to the next string every one second
  if (millis() > (timer + PATTERN_CHANGE_TIME)) {
    sevseg.setChars(testStrings[testStringsPos]);
    testStringsPos++;
    if (testStringsPos >= MAX_NUMBER_STRINGS) testStringsPos = 0;
    timer = millis();
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

