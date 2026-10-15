# Obstacle Avoiding Robot
An obstacle-avoiding robot simulation made using LPC2138 in Proteus 8 Professional.
The project uses an IR obstacle sensor to detect obstacles and an L293D motor driver to control two DC motors. The control logic is written in Embedded C and compiled using Keil µVision.

# Components Used

- LPC2138 ARM7 microcontroller
- IR obstacle sensor (custom Proteus library)
- L293D motor driver
- DC motors

# Files

- `main.c` - Source code
- `Obstacle_Robot.hex` - Compiled firmware
- `Obstacle_Robot.uvproj` - Keil project
- `LPC2138_Obstacle_Robot.pdsprj` - Proteus circuit

Note: The IR sensor required a separately downloaded Proteus library.
This project was developed and tested in simulation.

I made this project using Keil µVision 4 and Proteus 8 Professional. Compatibility with newer versions has not been verified.

Author: Saksham Joshi
