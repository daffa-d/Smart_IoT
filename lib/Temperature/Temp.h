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
    DHT dht(pin, DHT_TYPE);

    Temp(uint8_t pin, uint8_t DHT_TYPE)
    {
        Temp::pin = pin;
        Temp::DHT_TYPE = DHT_TYPE;
    }
    

private:
    float _Kelembapan;
    float _Suhu;
    bool _StateDHT = false;
};

class Suhu : public Temp
{
    public:
    float Process (float &humd, float &temp)
    {
        _Humd = humd;
        _Temp = temp;
    }

    private:
    float _Humd;
    float _Temp;
};

#endif
