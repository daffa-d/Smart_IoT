#include "Connection.h"

WiFiClient client;
WiFiManager wifiManager;

Connection::Connection(const char *SSID, const char *PASS)
{
  _SSID = SSID;
  _PASS = PASS;
}
void Connection::begin()
{

  WiFi.begin(_SSID, _PASS);
  uint32_t previousTime = 0;
  int Jeda = 5000;
  bool stateConnect = false;

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(300);
    unsigned long now = millis();
    if(now - previousTime >= Jeda)
    {
      previousTime = now;
      stateConnect = !stateConnect;
      if (stateConnect)
      {
        wifiManager.autoConnect("WiFi Manager");
      }
      
    }
  }
  Serial.print(F("Sukses Tersambung Dengan SSID "));
  Serial.println(WiFi.SSID());
}