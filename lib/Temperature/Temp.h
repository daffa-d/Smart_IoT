#ifndef Temp_h
#define Temp_h

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>

class Temp
{
public:
    uint8_t pin;
    uint8_t DHT_TYPE;

    Temp(uint8_t pin, uint8_t DHT_TYPE)
    {
        Temp::pin = pin;
        Temp::DHT_TYPE = DHT_TYPE;
    }
    void begin();

private:
    float _Kelembapan;
    float _Suhu;
    bool _StateDHT = false;
};

#endif
