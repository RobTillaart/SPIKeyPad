//    FILE: SPIKeyPad.cpp
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef (SPI implementation)
// VERSION: 0.0.1
//    DATE: 2026-04-11
// PURPOSE: SPI based 4x4 keypad driver using MCP23S08 GPIO expander
//     URL: https://github.com/RobTillaart/SPIKeyPad

#include "SPIKeyPad.h"

using namespace SPIKeyPadLib;

/// @brief Construct a new SPIKeyPad object
/// @param csPin Chip Select pin used for MCP23S08
SPIKeyPad::SPIKeyPad(uint8_t csPin) : _io(csPin) {}

/// @brief Initialize MCP23S08 and configure keypad pins
/// @return true if initialization succeeded
bool SPIKeyPad::begin()
{
    if (!_io.begin())
        return false;

    // Configure rows (OUTPUT, default HIGH)
    for (uint8_t pin = FIRST_ROW_PIN; pin < FIRST_ROW_PIN + ROW_COUNT; ++pin)
    {
        _io.pinMode1(pin, OUTPUT);
        _io.write1(pin, HIGH);
    }

    // Configure columns (INPUT with pull-up)
    for (uint8_t pin = FIRST_COL_PIN; pin < FIRST_COL_PIN + COL_COUNT; ++pin)
    {
        _io.pinMode1(pin, INPUT);
        _io.setPullup(pin, true);
    }

    return true;
}

/// @brief Scan the keypad matrix and return key index
/// @return key index (0–15) or NO_KEY if none pressed
uint8_t SPIKeyPad::_scanKeypad()
{
    for (uint8_t row = FIRST_ROW_PIN; row < FIRST_ROW_PIN + ROW_COUNT; ++row)
    {
        _io.write1(row, LOW);

        uint8_t state = _io.read8();
        uint8_t cols = (state >> COL_SHIFT) & COL_MASK;

        for (uint8_t col = 0; col < COL_COUNT; ++col)
        {
            if ((cols & (1 << col)) == 0)
            {
                _io.write1(row, HIGH);
                return row * COL_COUNT + col;
            }
        }

        _io.write1(row, HIGH);
    }

    return NO_KEY;
}

/// @brief Get the currently pressed key
/// @return key index (0–15) or NO_KEY
uint8_t SPIKeyPad::getKey()
{
    return _scanKeypad();
}

/// @brief Check if any key is currently pressed
/// @return true if a key is pressed
bool SPIKeyPad::isPressed()
{
    return getKey() != NO_KEY;
}
