/*
  Author: Tobias Grundtvig
*/

#include <Arduino.h>
#include "LEDPattern.h"

LEDPattern::LEDPattern(const uint8_t ledPin, bool ledON)
{
    _ledPin = ledPin;
    _ledON = ledON;
    _ledValue = !ledON;
    _state = 0;
    _lastChange = 0;
    _status = LED_PATTERN_STATUS_OFF;
    _length = 5;
    _pattern[0] = 100;
    _pattern[1] = 200;
    _pattern[2] = 100;
    _pattern[3] = 1200;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledON);
}

void LEDPattern::update(unsigned long curTime)
{
    if(_status == LED_PATTERN_STARTING)
    {
        _status = LED_PATTERN_STATUS_PATTERN;
        _state = 0;
        _ledValue = _ledON;
        digitalWrite(_ledPin, _ledValue);
        _lastChange = curTime;
    }
    else if(_status == LED_PATTERN_STATUS_PATTERN && curTime -_lastChange >= _pattern[_state])
    {
        _ledValue = !_ledValue;
        _lastChange += _pattern[_state];
        ++_state;
        if(_state >= _length)
        {
            _state = 0;
            _ledValue = _ledON;
        }
        digitalWrite(_ledPin, _ledValue);
    }
}

 uint8_t LEDPattern::getStatus()
 {
     if(_status == LED_PATTERN_STARTING)
     {
         return LED_PATTERN_STATUS_PATTERN;
     }
     return _status;
 }

void LEDPattern::setLED(bool on)
{
    _status = on ? LED_PATTERN_STATUS_ON : LED_PATTERN_STATUS_OFF;
    digitalWrite(_ledPin, on ? _ledON : !_ledON);
}

void LEDPattern::start()
{
    _status = LED_PATTERN_STARTING;
}

void LEDPattern::stop()
{
    _status = LED_PATTERN_STATUS_OFF;
    digitalWrite(_ledPin, !_ledON);
}

void LEDPattern::setBlinksPattern(uint8_t count, uint16_t lightPeriod, uint16_t darkPeriod, uint16_t pausePeriod)
{
    count = min((int) count, LED_PATTERN_MAX_SIZE / 2);
    _length = 0;
    for(uint8_t i = 0; i < count; ++i)
    {
        _pattern[_length++] = lightPeriod;
        _pattern[_length++] = darkPeriod;
    }
    _pattern[_length-1] = darkPeriod + pausePeriod;
    if(_status == LED_PATTERN_STATUS_PATTERN)
    {
        _status = LED_PATTERN_STARTING;
    }
}

void LEDPattern::setLength(uint16_t length)
{
    _length = length;
}

void LEDPattern::setPos(uint16_t index, uint16_t milliSeconds)
{
    _pattern[index] = milliSeconds;
}