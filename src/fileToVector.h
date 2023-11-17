#ifndef fileToVector_h
#define fileToVector_h

#include <Arduino.h>
#include <SD.h>
#include <vector>

class fileToVector{
    public:
        fileToVector();
        std::vector<String> toStringVector(File file);
        std::vector<String> splitString(String input, char character);
        std::vector<std::vector<int>> toIntVector(String input);
};

#endif