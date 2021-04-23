#include <Arduino.h>
#include "Firebase.h"
#include "Connection.h"
//#include "Temp.h"

FB fb; //class object dari library firebase
Connection AT("b4871e", "277123586"); //SSID,PASS, Autoconnect Wifimanager WebServer jika lebih dari 5 Detik
getDataRelay GDR_1(16); // Data Relay True or False dari Firebase ke pin GPIO 16
getDataRelay GDR_2(00); // Data Relay True or False dari Firebase ke pin GPIO 0


int dataRelay_1;
int dataRelay_2;

void setup()
{
  Serial.begin(115200);
  AT.begin();

  fb.begin("https://iot-kuu.firebaseio.com/", "Mc8IsWCPEVtRhU2Mbn16RnijhUnOXyTI4FFMg1H2");
  Firebase.reconnectWiFi(true);
  GDR_1.begin();
  GDR_2.begin();
}

void loop()
{
  GDR_1.getData_Relay("/Relay_1", dataRelay_1);
  GDR_2.getData_Relay("/Relay_2", dataRelay_2);
}