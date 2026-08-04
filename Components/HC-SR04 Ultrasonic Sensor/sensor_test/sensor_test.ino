#include <SevSeg.h>

#define UPDATE_INTERVAL 200
#define TRIG_PIN 13
#define ECHO_PIN 0

// Global variables and objects
SevSeg sevseg;
unsigned long previous_time = 0;
int current_num = 0; 
float duration, distance;

void setup() {
    // Display setup
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

    //Sensor setup
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    delay(10);
}

void loop() {
    unsigned long current_time = millis();

 // Only ping the sensor (the blocking part) once per interval
    if (current_time - previous_time >= UPDATE_INTERVAL) {
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        duration = pulseIn(ECHO_PIN, HIGH, 18000UL);
        distance = duration * 0.034 / 2;

        sevseg.setNumberF(distance, 0);
        previous_time = current_time;
    }

    // Runs every loop, uninterrupted by pulseIn's blocking time
    sevseg.refreshDisplay();
}

