/*
Arduino -> Microcontroller
D2 -> PD2 -> serial data
D3 -> PD3 -> serial clock
D4 -> PD4 -> clear register (active low)
D6 -> PD6 -> latch pin 
*/

#define PORTD *((volatile byte*) 0x2B)
#define DDRD *((volatile byte*) 0x2A)

#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6

#define BIT_SET(reg, bit)   ((reg) |= (1 << (bit)))
#define BIT_CLEAR(reg, bit) ((reg) &= ~(1 << (bit)))
#define BIT_TOGGLE(reg, bit) ((reg) ^= (1 << (bit)))
#define BIT_READ(reg, bit)  (((reg) >> (bit)) & 1)

int loop_var = 0;
byte output = 120; // set your output value here

void setShiftRegister(byte value){
  BIT_CLEAR(PORTD, D6);
  sendData(D3, D2, value);
  BIT_SET(PORTD, D6);
};

void sendData(int clock_pin, int data_pin, byte value){
  // Assume LSB first
  for (int i = 0; i < 8; i++){
    if ((value & 1) == 1){
      BIT_SET(PORTD, data_pin);
    } else {
      BIT_CLEAR(PORTD, data_pin);
    }
    value >>= 1;
    BIT_SET(PORTD, clock_pin);
    BIT_CLEAR(PORTD, clock_pin);
		}
};

void setup() {
  // Set pins D2-D5 to output
  BIT_SET(DDRD, D2);
  BIT_SET(DDRD, D3);
  BIT_SET(DDRD, D4);
  BIT_SET(DDRD, D5);
  BIT_SET(DDRD, D6);

  BIT_SET(PORTD, D4);
}

void loop() {

  // Set byte value
  if (loop_var == 0){
    setShiftRegister(output);
  }
  loop_var = 1;
}
