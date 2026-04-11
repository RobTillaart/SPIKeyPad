//    FILE: SPIKeyPad.h
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef (SPI implementation)
// VERSION: 0.0.1
//    DATE: 2026-04-11
// PURPOSE: SPI based 4x4 keypad driver using MCP23S08 GPIO expander
//     URL: https://github.com/RobTillaart/SPIKeyPad

#pragma once

#include <Arduino.h>
#include <MCP23S08.h>

#define SPI_KEYPAD_LIB_VERSION (F("0.0.1"))

namespace SPIKeyPadLib
{
    /// @brief Returned when no key is pressed
    constexpr uint8_t NO_KEY = 16;

    /// @brief First GPIO pin used for rows (GP0–GP3)
    constexpr uint8_t FIRST_ROW_PIN = 0;

    /// @brief First GPIO pin used for columns (GP4–GP7)
    constexpr uint8_t FIRST_COL_PIN = 4;

    /// @brief Number of rows in keypad
    constexpr uint8_t ROW_COUNT = 4;

    /// @brief Number of columns in keypad
    constexpr uint8_t COL_COUNT = 4;

    /// @brief Bit shift to extract column bits from read8()
    constexpr uint8_t COL_SHIFT = FIRST_COL_PIN;

    /// @brief Bit mask for column bits (4 bits)
    constexpr uint8_t COL_MASK = 0x0F;
}

/// @brief SPI based 4x4 keypad driver using MCP23S08
class SPIKeyPad
{
public:
    /// @brief Construct a new SPIKeyPad object
    /// @param csPin Chip Select pin used for MCP23S08
    explicit SPIKeyPad(uint8_t csPin);

    /// @brief Initialize keypad and underlying MCP23S08
    /// @return true if initialization succeeded
    [[nodiscard]] bool begin();

    /// @brief Get the currently pressed key
    /// @return key index (0–15) or SPIKeyPadLib::NO_KEY
    [[nodiscard]] uint8_t getKey();

    /// @brief Check if any key is currently pressed
    /// @return true if a key is pressed
    [[nodiscard]] bool isPressed();

private:
    MCP23S08 _io;

    /// @brief Scan keypad matrix (internal)
    /// @return key index (0–15) or SPIKeyPadLib::NO_KEY
    uint8_t _scanKeypad();
};