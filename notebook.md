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
was able to get a smooth looking display without using interrupts. I will be using interrupts in the future however.

## Shift Register (SNx74HC595)
At this point, I notice that I am almost out of pins on the Arduino. One solution to this problem is to use a shift register
so that a few pins can map to a multitude of output pins.

I found [this](https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/) tutorial which helped immensely with understanding
the purpose of each pin. The data sheet from Texas Instruments was useful but too verbose for me. 

### Bare Metal Shift Register
For this, I needed to know where registers were stored that I needed.

## Bare Metal Experimentation
I decided that I should familiarize myself with the low level coding behind the scenes of the Arduino package. I decided to try the LED blink program without
using the Arduino package. The hardest part about this was learning the datasheet since I was already comfortable with pointers in C.