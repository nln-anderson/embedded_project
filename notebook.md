# Notebook
The contains all my day-to-day notes about testing and so forth.

## 4 Digit Display (5461AS)
The first piece I wanted to get familiar with was the 4 digit display. The setup is more simple than the LCD that I eventually want to use.
In fact, I could end up using this 4 digit display in the final project if it is a better fit.

I found the datasheet for the part. The part is called 5461AS-1. Here is what I gathered from the datasheet as well as the resource
found at this [link](https://thomas.bibby.ie/using-the-kyx-5461as-4-digit-7-segment-led-display-with-arduino/).

### Datasheet Key Takeaways
- The device is a common cathode display, meaning all the input pins flow into the output pin for each digit.
- Each digit is controlled individually with pins 6, 8, 9, and 12. The remaining pins determine the segments.
- Forward voltage drop is about 1.8V
- The segments are organized as in this [image](https://commons.wikimedia.org/wiki/File%3A7_segment_display_labeled.svg).

To make testing easier, I decided to connect the pins from the Arduino to match the pins on the display by number. For example,
pin 1 on the Arduino matches to pin 1 on the display.

With that, I made a simple program that counts up to 10 on the display. In this program, I made a basic function to map digits to the required pins. I
was going to expand this function for bigger numbers and decimals, but I found this [library](https://github.com/untr0py/SevSeg) instead. A key
point I noticed is that I shouldn't use the delay function since it locks up the program.

## Ultrasonic Sensor (HC-SR04)
This is the piece I really wanted to work with. I found a [datasheet/tutorial](https://www.handsontec.com/dataspecs/HC-SR04-Ultrasonic.pdf).

### Datasheet Key Takeaways
- The Trigger pin should be activated for 10µs to generate the 40KHz burst.
- Once the burst has been sent, the Echo pin will set to HIGH in proportion to the time it takes for the audio signal to return.
- Therefore, distance = HIGH time * 340 m/s ÷ 2

In my coding, I found the biggest challenge to be timing. Without using interrupts, it is hard to prevent blinking on the LED. But, I
was able to get a smooth looking display without using interrupts. See sensor_test.ino for the code.
I plan to use interrupts in the future however.

## Shift Register (SNx74HC595)
At this point, I notice that I am almost out of pins on the Arduino. One solution to this problem is to use a shift register
so that a few pins can map to a multitude of output pins.

I found [this](https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/) tutorial which helped immensely with understanding
the purpose of each pin. The data sheet from Texas Instruments was useful but too verbose for me. Here is the summary I gather:
- SRCLK is the clock pin. Data is shifted and stored when this goes from low to high.
- SER is the data pin. This will store a 1 if high and a 0 if low.
- RCLK is the latch pin. This moves the stored value to the output value. Idea being, you only want to update the register
when the full value has been populated.
- The rest of the pins will remain static or will act as output pins.

## Bare Metal Experimentation
I decided that I should familiarize myself with the low level coding behind the scenes of the Arduino package. I decided to try the LED blink program without
using the Arduino package. The hardest part about this was learning the datasheet since I was already comfortable with pointers in C.

I was successful with a basic program to set the shift register output. I decided this was not worth pursing unless
I saw significant performance issues with using the standard libraries.

## Shift Register with Display
This was part of the project I was worried about. While I don't have to use the shift register, I believe its a good idea to clear up
pins in case I want to add other components later. My concern is that the serial update will not be fast enough to prevent the 
display from flickering.

The idea was to use the shift register for the 7 segment pins. That way, 3 pins will control 7, opening up 4 extra pins.

| Arduino Pin | Component | Component Pin |
| ---        |    ----   |          --- |
| 2     | Display    | Digit 1   |
| 3 | Display        | Digit 2      |
| 4 | Display        | Digit 3      |
| 5 | Display        | Digit 4      |
| 6 | Shift Register | Data (SER)   |
| 7 | Shift Register | Latch (RCLK)|
| 8 | Shift Register | Clock (SRCLK)|
| 9 | Shift Register | Clear (SRCLR)|

I wrote my own functions so that I have control over the process. One of the first challenges I faces was timing (again).
Since I wrote the functions, the SRCLR pulse was not long enough to reset the register. I consulted the spec sheet and 
found that the timing requirement is about 20 nano seconds. I decided to use a 1 microsecond delay since this is 
the smallest time interval that you can easily use on Arduino. This is something on want to revisit to optimize.

