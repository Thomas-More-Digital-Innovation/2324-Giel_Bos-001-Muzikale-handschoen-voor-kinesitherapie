#ifndef fileToVector_h
#define fileToVector_h

#include <Arduino.h>
#include <vector>
#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card

std::vector<String> toStringVector(File file);
std::vector<String> splitString(String input, char character);
std::vector<std::array<int, 3>> toIntVector(String input);

#endif