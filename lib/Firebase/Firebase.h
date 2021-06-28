#ifndef Firebase_h
#define Firebase_h

#include "Arduino.h"
#include "FirebaseESP8266.h"

class FB
{
public:
    //int dataRelay1(int data);
    void begin(const String Host, const String Auth);
    void sendDataInt(int time, const String &path_db, int value);
    void sendDataFloat(int time, const String &path_db, float value);

private:
};

class getDataRelay
{
public:
    getDataRelay(uint8_t pin);
    getDataRelay(uint8_t pin, uint8_t pinBuzzer);
    void begin();
    int run(const char *pathDB, int &dataRelay);
    int run(const char *pathDB, int &dataRelay,
            bool StateBuzzer);

private:
    uint8_t _pin;
    uint8_t _pinBuzzer;
    String _get = "";
    bool stateData = false;
};

#endif