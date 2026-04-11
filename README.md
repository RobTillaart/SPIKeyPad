# SPIKeyPad

Arduino library for 4x4 (or smaller) keypad connected to an SPI MCP23S08.


## Description

The SPIKeyPad library implements reading of a 4x4 keypad using the MCP23S08 SPI GPIO expander.

It is conceptually similar to the I2CKeyPad library, but uses SPI instead of I2C,
allowing faster scanning of the keypad.


## Features

- 4x4 keypad scanning via MCP23S08
- SPI-based communication (faster than I2C)


## Connection

The MCP23S08 is connected between the processor and the keypad matrix.
```
    MCU              MCP23S08              KEYPAD
 +--------+        +---------+          +---------+
 |        |        |       0 |<-------->| ROW     |
 |   SPI  |<------>|       1 |<-------->| ROW     |
 |        |        |       2 |<-------->| ROW     |
 |        |        |       3 |<-------->| ROW     |
 |        |        |         |          |         |
 |        |        |       4 |<-------->| COL     |
 |        |        |       5 |<-------->| COL     |
 |        |        |       6 |<-------->| COL     |
 |        |        |       7 |<-------->| COL     |
 +--------+        +---------+          +---------+
```


## Interface

```cpp
#include "SPIKeyPad.h"
```


## Constructor

- **SPIKeyPad(uint8_t csPin)**  
  Create a keypad instance using the given Chip Select pin.


## Functions

- **bool begin()**  
  Initializes the MCP23S08 and configures the keypad pins.

- **uint8_t getKey()**  
  Returns a key index from **0 to 15**.  
  Returns **SPIKeyPadLib::NO_KEY (16)** if no key is pressed.

- **bool isPressed()**  
  Returns true if any key is currently pressed.


## Tooling Notes

### Compiler Warnings (Arduino IDE)

This library uses ```[[nodiscard]]``` to help detect ignored return values.  
However, Arduino IDE disables compiler warnings by default.  
To benefit from this feature, enable warnings:

> File > Preferences > Compiler warnings > Default (or higher)

### PlatformIO

Warnings are enabled by default, no additional configuration required.


## Related

- https://github.com/RobTillaart/I2CKeyPad
- https://github.com/RobTillaart/MCP23S08


## Future

#### Must

#### Should

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,