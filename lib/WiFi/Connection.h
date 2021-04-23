#ifndef Connection_h
#define Connection_h

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

class Connection
{
    public:
    Connection(const char *SSID, const char *PASS);
    void begin();

    private:
    const char* _SSID;
    const char* _PASS;
};

#endif