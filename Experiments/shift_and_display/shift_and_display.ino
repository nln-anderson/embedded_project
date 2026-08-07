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

int loop_var = 0;
void loop() {
  byte test = digitPatterns[3];
  if (loop_var == 0) {
   setShiftRegister(PIN_6, PIN_8, PIN_7, PIN_9, test);
   loop_var = 1;
  }
}
