# Embedded Circuit Project
The goal of this project is two fold:
1. Build a device that measures and displays object distance.
2. Familiarize myself with building embedded systems.

The day-to-day work is found in the notebook.md file. The final build is the source.ino file. You will also
find many other .c or .ino files in this project. They were mostly created to learn and test some of the
functionality of the components.

At this point, the project has a completed bread-board demo. I eventually want to order some perf boards
to solder together a compact version of the final product.

# Pinout Configuration
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
| 10 | Ultrasonic Sensor | Trig |
| 11 | Ultrasonic Sensor | Echo |
