//    FILE: SPIKeyPad_4x4.ino
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef
// PURPOSE: demo 4x4 keypad
//     URL: https://github.com/RobTillaart/SPIKeyPad
//
//  MCP23S08 (SPI)
//    GP0–GP3 rows
//    GP4–GP7 columns

#include <SPIKeyPad.h>

SPIKeyPad keypad(10); // CS pin

void setup()
{
    Serial.begin(115200);

    Serial.println("SPIKeyPad test");

    if (!keypad.begin())
    {
        Serial.println("Failed to initialize keypad!");
        while (1);
    }

    Serial.println("Keypad initialized.");
}

void loop()
{
    uint8_t key = keypad.getKey();

    if (key != SPIKeyPadLib::NO_KEY)
    {
        Serial.print("Key pressed: ");
        Serial.println(key);
    }
}