#include <Arduino.h>
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring
#include <ledring.h>

ledring::ledring(Adafruit_NeoPixel ring){
    _ledring = ring;
}

void ledring::off(){
    _ledring.clear();
}

void ledring::showFigure(std::array<std::array<uint32_t, 3>, 12> figure, int brightness){
    _ledring.setBrightness(brightness);
    for(int i = 0; i < figure.size(); i++){
        if (i >= 0 && i < _ledring.numPixels()) {
            _ledring.setPixelColor(i,figure[i][0],figure[i][1],figure[i][2]);
        }
    }
    _ledring.show();
}