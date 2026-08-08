// Define pins
const int PIN_2 = 2; // Dig 1
const int PIN_3 = 3; // Dig 2
const int PIN_4 = 4; // Dig 3
const int PIN_5 = 5; // Dig 4

// 74HC595
const int PIN_6 = 6; // Data
const int PIN_7 = 7; // Latch
const int PIN_8 = 8; // Clock
const int PIN_9 = 9; // Clear, active low

// Group pins into an array for easy setup
const int PINS[] = {PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9};
const int NUM_PINS = sizeof(PINS) / sizeof(PINS[0]);

// Which segments are ON for each digit 0-9, packed as bits: dp,g,f,e,d,c,b,a (bit8...bit1)
// dp (bit8) is unused, so it's always 0
const byte digitPatterns[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

void setup() {
  // Set pins as output mode and initialize them all to LOW
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(PINS[i], OUTPUT);
    digitalWrite(PINS[i], LOW);
  }

  // Set the active low pins to high
  digitalWrite(PIN_9, HIGH);

}

void sendSerialData(int data_pin, int clock_pin, byte value){
  // This sends data through the serial link. It assumes the most significant bit is sent first.
    for (int i = 0; i < 8; i++){
      if ((value & 128) != 0){
        digitalWrite(data_pin, 1);
      } else {
        digitalWrite(data_pin, 0);
      }
      value <<= 1;
      digitalWrite(clock_pin, 1);
      digitalWrite(clock_pin, 0);
      }
}

void setShiftRegister(int data_pin, int clock_pin, int latch_pin, int clear_pin, byte value){
  // This is the start to finish function to save and output a new value on the shift register
  // First, set the clear pin low then high
  digitalWrite(clear_pin, LOW);
  delayMicroseconds(1);
  digitalWrite(clear_pin, HIGH);

  // Second, we send the data
  sendSerialData(data_pin, clock_pin, value);

  // Third, move the register to the output
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}

void displayNumber(int data_pin, int clock_pin, int latch_pin, int clear_pin, int digit_1, int digit_2, int digit_3, int digit_4, int brightness ,int value){
  // Given a byte input, this should display the correct number. Assumes a shift register is used.
  // Turn all digits off to begin
    digitalWrite(digit_1, HIGH);
    digitalWrite(digit_2, HIGH);
    digitalWrite(digit_3, HIGH);
    digitalWrite(digit_4, HIGH);

  // Check if number is within range < 9999
  if (value >= 9999){
    // Set the segment to 9
    setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[9]);
    digitalWrite(digit_1, LOW);
    digitalWrite(digit_2, LOW);
    digitalWrite(digit_3, LOW);
    digitalWrite(digit_4, LOW);
  }
  else if (value <= 0){
    // Only enable digit 4
    setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[0]);
    digitalWrite(digit_4, LOW);
  }
  else {
    // main body of function. Takes an integer and displays it.
    int digit;
    digit = value / 1000;
      if (digit >= 1){
        setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[digit]);
        digitalWrite(digit_1, LOW);
        delayMicroseconds(brightness);
        digitalWrite(digit_1, HIGH);
        value = value - digit *1000;
      }

      digit = value / 100;
      if (digit >= 1){
        setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[digit]);
        digitalWrite(digit_2, LOW);
        delayMicroseconds(brightness);
        digitalWrite(digit_2, HIGH);
        value = value - digit *100;
      }

      digit = value / 10;
      if (digit >= 1){
        setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[digit]);
        digitalWrite(digit_3, LOW);
        delayMicroseconds(brightness);
        digitalWrite(digit_3, HIGH);
        value = value - digit *10;
      }

      digit = value;
      if (digit >= 1){
        setShiftRegister(data_pin, clock_pin, latch_pin, clear_pin, digitPatterns[digit]);
        digitalWrite(digit_4, LOW);
        delayMicroseconds(brightness);
        digitalWrite(digit_4, HIGH);
        }
    }
}

int loop_var = 0;
void loop() {
  displayNumber(PIN_6, PIN_8, PIN_7, PIN_9, PIN_2, PIN_3, PIN_4, PIN_5, 500, 123);
  byte test = digitPatterns[5];
  if (loop_var == 0) {
   //setShiftRegister(PIN_6, PIN_8, PIN_7, PIN_9, test);
   //loop_var = 1;
  }
}
