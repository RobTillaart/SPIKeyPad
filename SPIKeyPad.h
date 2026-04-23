#pragma once
//
//    FILE: SPIKeyPad.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-04-09
// PURPOSE: Arduino library for 4x4 KeyPad connected to an SPI MCP23S08
//     URL: https://github.com/RobTillaart/SPIKeyPad


#include "Arduino.h"
#include "SPI.h"
#include <MCP23S08.h>

#define SPI_KEYPAD_LIB_VERSION    (F("0.1.0"))

#define SPI_KEYPAD_NOKEY          16
#define SPI_KEYPAD_FAIL           17
//
#define SPI_KEYPAD_THRESHOLD      255


//  experimental
#define SPI_KEYPAD_4x4            44
#define SPI_KEYPAD_5x3            53
#define SPI_KEYPAD_6x2            62
#define SPI_KEYPAD_8x1            81


class SPIKeyPad
{
public:
  SPIKeyPad(int cs);
  SPIKeyPad(int cs, SPIClass* spi);
  SPIKeyPad(int cs, int address, SPIClass* spi);
  ~SPIKeyPad();

  //  initialize SPI before calling begin()
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  get raw key's 0..15
  uint8_t  getKey();
  uint8_t  getLastKey();
  bool     isPressed();

  //  get 'translated' keys
  //  user must load KeyMap, there is no check.
  uint8_t  getChar();
  uint8_t  getLastChar();
  void     loadKeyMap(char * keyMap);   //  char[19]

  //  mode functions - experimental
  void     setKeyPadMode(uint8_t mode = SPI_KEYPAD_4x4);
  uint8_t  getKeyPadMode();

  //  value in milliseconds, max 65535 ms
  void     setDebounceThreshold(uint16_t value = 0);
  uint16_t getDebounceThreshold();
  uint32_t getLastTimeRead();


protected:
  MCP23S08* _io;

  uint8_t  _lastKey;
  uint8_t  _mode;
  uint8_t  _read(uint8_t mask);
  uint16_t _debounceThreshold;
  uint32_t _lastTimeRead;

  uint8_t  _getKey4x4();
  uint8_t  _getKey5x3();
  uint8_t  _getKey6x2();
  uint8_t  _getKey8x1();
  
  char *  _keyMap = NULL;
};


//  -- END OF FILE --

