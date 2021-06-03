#ifndef Firebase_h
#define Firebase_h

#include "Arduino.h"
#include "FirebaseESP8266.h"

class FB
{
public:
    //int dataRelay1(int data);
    void begin(const String Host, const String Auth);
    void sendDataInt(int time, const String path_db, int value);
    void sendDataFloat(int time, const String path_db, float value);

private:
    int _time;
    int _pin;
    int _valueInt;
    float _valueFloat;
    const String _path_db;
};

class getDataRelay
{
public:
    getDataRelay(uint8_t pin);
    void begin(bool serial = false);
    int getData_Relay(const char *pathDB, int &dataRelay);

private:
    uint8_t _pin;
    boolean _serial = false;
};

#endif