#ifndef ledring_h
#define ledring_h
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring

class ledring{
    public:
    ledring(Adafruit_NeoPixel ring);
    void off();
    void showFigure(std::array<std::array<uint32_t, 3>, 12> figure, int brightness);
    private:
        Adafruit_NeoPixel _ledring;
};

#endif