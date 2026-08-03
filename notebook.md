# Notebook
The contains all my day-to-day notes about testing and so forth.

## 4 Digit Display
The first piece I wanted to get familiar with was the 4 digit display. The setup is more simple than the LCD that I eventually want to use.
In fact, I could end up using this 4 digit display in the final project if it is a better fit.

I found the datasheet for the part. The part is called 5461AS-1. Here is what I gathered from the datasheet as well as the resource
found at this [link](https://thomas.bibby.ie/using-the-kyx-5461as-4-digit-7-segment-led-display-with-arduino/).

### Key Takeways
- The device is a common cathode display, meaning all the input pins flow into the output pin for each digit.
- Each digit is controlled individually with pins 6, 8, 9, and 12. The remaining pins determine the segments.
- Forward voltage drop is about 1.8V
- The segments are organized as in this [image](https://commons.wikimedia.org/wiki/File%3A7_segment_display_labeled.svg).

To make testing easier, I decided to connect the pins from the Arduino to match the pins on the display by number. For example,
pin 1 on the Arduino matches to pin 1 on the display.

With that, I made a simple program that counts up to 10 on the display.