# Project Title

Smart led strip that can be controlled by your phone and will create magical atmosphere at your house

## Features

- Simple color mode
- Continuous color change
- Microphone amplifier mode
- Displaying information
- Connection to bluetooth

## Usage

Just plug in your power supply and connect through bluetooth using any bluetooth terminal software

You can change your led and display mode by following messages:

#### PulseMode

```bash
 m0;{param1};{param2}
 ```

Changes the color of the led to *{param1}* (see the table of int to color below); the color decreases in brightness
until it disappears completely in *{param2}* seconds

### ContinuousTransformationMode

```bash
 m1;{param1}
 ```

Iterating through colors with decreases in brightness until it disappears completely in *{param1}* seconds

### ContinuousColorChangeMode

```bash
 m2;{param1}
 ```

Iterating through colors list changing it every *{param1}*

### RandomColorMode

 ```bash
 m3;{param1}
 ```

Randomly change color every *{param1}* seconds

### MicrophoneMode

 ```bash
 m4;{param1};{param2}
 ```

Color set to *{param1}*. Color brightness depends on the volume around the device. Color brightness changes every
*{param2}* seconds

### Simple color

```bash
 {param1};{param2};{param3}
 ```

Color set to these 3 parametrs using RGB format

#### OR

```bash
c{param1}
 ```

Set color to param1 according to table below

### Color list

| Number | Color   |
|--------|---------|
| 0      | RED     |
| 1      | GREEN   |
| 2      | BLUE    |
| 3      | YELLOW  |
| 4      | MAGENTA |
| 5      | CYAN    |
| 6      | WHITE   |
| 7      | ORANGE  |
| 8      | PURPLE  |
| 9      | PINK    |
| 10     | BROWN   |

## Display configuration

### Enable display

 ```bach
 d1
 ```

Enables display that show the RGB format of current color

## 🤖 Used hardware

**Necessery hardware**
| Component name | Аmount |
| - |-
| **NucleoF401RET6** | 1 |
| **LCD 5110** | 1 |
| **MAX4466** | 1 |
| **HC-05** | 1 |
| **Resistors 10kOm and 220Om** | many |
| **Logical MOSFET like IRLZ44N** | 3 |
|**12 Volt LED strip** | 1|
| **Power supply with 12volt and 5volt** | 1 |
| **Jumpers**| ∞|

**Additional/ debug hardware**

- Multimeter

- Oscilloscope (*buy me one pls*)

- Usb ttl converter

## 🖥️ Used software

- U can use whatever ide you like for writing code, i prefer JetBrains product aka CLion because it has great code
  editor with amazing features and gorgeous design.
- For uploading and debugging STM32 i like STM32CubeIDE that provides amazing capabilities for Embedded developers.
- Also STM32CubeMX saves a lot of time at configuration
- Any Serial port monitor for configuration your hc-05

## 🛠 Skills and technology

*Communaction Interfaces*:

- SPI
- UART
- GPIO
  *Data Handling*:
- Polling
- Interrupts
  *Other*:
- C programming language
- PWM
- ADC
- Timers
- Software and hardware debugging
- Circuity

## Roadmap

- Add temperature and humidity sensors and display data from them on the display(❌)

- Add GFSK modulation based module as alternative way of wireless communicatio(❌)
- Create User Interface for mobile (❌)

## 🔗 Links

[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/artem-barasii-926525271/)

