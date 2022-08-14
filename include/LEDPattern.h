/*
  Author: Tobias Grundtvig
*/

#ifndef LEDPattern_h
#define LEDPattern_h

#include <Arduino.h>

#define LED_PATTERN_STATUS_OFF 0
#define LED_PATTERN_STATUS_ON 1
#define LED_PATTERN_STATUS_PATTERN 2


#define LED_PATTERN_STARTING 255
#define LED_PATTERN_MAX_SIZE 64

class LEDPattern
{
public:
    LEDPattern(const uint8_t ledPin, bool ledON);
    void update(unsigned long curTime);
    void setLED(bool on);
    uint8_t getStatus();
    void start();
    void stop();
    void setBlinksPattern(uint8_t count, uint16_t lightPeriod, uint16_t darkPeriod, uint16_t pausePeriod);
    void setLength(uint16_t length);
    void setPos(uint16_t index, uint16_t milliSeconds);
private:
    uint16_t _pattern[LED_PATTERN_MAX_SIZE];
    uint16_t _length;
    uint16_t _state;
    uint8_t _ledPin;
    uint8_t _status;

    unsigned long _lastChange;
    bool _ledValue;
    bool _ledON;
};

#endif