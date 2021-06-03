#include "Firebase.h"
//#include "Arduino.h"

FirebaseData fbdo;

void FB::begin(const String Host, const String Auth)
{
  Firebase.begin(Host, Auth);
}

void FB::sendDataInt(int time, const String path_db, int value)
{
  _time = time;
  _path_db == path_db;
  _valueInt = value;

  Serial.print(F("Data Yang Dikirim Adalah (Interger) = "));
  Serial.println(_valueInt);
  Firebase.setInt(fbdo, path_db, _valueInt);
  delay(_time);
}

void FB::sendDataFloat(int time, const String path_db, float value)
{
  _time = time;
  _path_db == path_db;
  _valueFloat = value;

  Serial.print(F("Data Yang Dikirim Adalah (Float) = "));
  Serial.println(value);
  Firebase.setFloat(fbdo, path_db, value);
  delay(time);
}

getDataRelay::getDataRelay(uint8_t pin)
{
  _pin = pin;
}

void getDataRelay::begin(boolean serial)
{
  pinMode(_pin, OUTPUT);
  _serial = serial;
}

int getDataRelay::getData_Relay(const char *pathDB, int &dataRelay)
{
  if (Firebase.getInt(fbdo, pathDB))
  {
    dataRelay = fbdo.intData();
    if (_serial == true)
    {
      Serial.print(F("Nilai Relay Pin Ke "));
      Serial.print(_pin);
      Serial.print(F(" Adalah = "));
    }
    Serial.println(dataRelay);
    if (dataRelay == 1)
    {
      digitalWrite(_pin, HIGH);
      if (_serial == true)
      {
        Serial.print(F("Relay Pin ke "));
        Serial.print(_pin);
        Serial.println(F(" Aktif"));
        Serial.println();
         Serial.println();
      }
    }
    else if (dataRelay == 0)
    {
      digitalWrite(_pin, LOW);
      if (_serial == true)
      {
        Serial.print(F("Relay Pin ke "));
        Serial.print(_pin);
        Serial.println(F(" Tidak Aktif"));
        Serial.println();
         Serial.println();
      }
    }
    else
    {
      Serial.println(F("Tidak Menerima Data"));
    }
  }
  else
  {
    Serial.println(fbdo.errorReason());
  }

  return dataRelay;
}
