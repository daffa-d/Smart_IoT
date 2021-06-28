#include "Firebase.h"

/**
 * @file Firebase.cpp
 * 
 * @mainpage Library For Get data, Send data, and activate relay from firebase
 * 
 */

FirebaseData fbdo;

void FB::begin(const String Host, const String Auth)
{
  Firebase.begin(Host, Auth);
}

void FB::sendDataInt(int time, const String &path_db, int value)
{
  //Serial.print(F("Data Yang Dikirim Adalah (Interger) = "));
  //Serial.println(value);
  Firebase.setInt(fbdo, path_db, value);
  delay(time);
}

void FB::sendDataFloat(int time, const String &path_db, float value)
{
  //Serial.print(F("Data Yang Dikirim Adalah (Float) = "));
  //Serial.println(value);
  Firebase.setFloat(fbdo, path_db, value);
  delay(time);
}

/*!
   * @param pin 
   *        pin For relay. input with connected relay
   * @param buzzer
   *        buzzer flagging. true for active buzzer. false for deactive buzzer
   * @param serial
   *        for active serial print relay
   */

getDataRelay::getDataRelay(uint8_t pin)
{
  getDataRelay::_pin = pin;
}

getDataRelay::getDataRelay(uint8_t pin, uint8_t pinBuzzer)
{
  _pin = pin;
  _pinBuzzer = pinBuzzer;
}

void getDataRelay::begin()
{
  pinMode(_pin, OUTPUT);
  pinMode(_pinBuzzer, OUTPUT);
}

/*!
 * @brief Get Data From Firebase Database
 * @param pathDB
 *        path Realtime Database from Firebase
 * @param dataRelay
 *        add value from database to global variabel / arguments
 */

int getDataRelay::run(const char *pathDB, int &dataRelay)
{
  if (Firebase.getInt(fbdo, pathDB))
  {
    dataRelay = fbdo.intData();
    if (dataRelay == 1)
    {
      digitalWrite(_pin, HIGH);
    }
    else if (dataRelay == 0)
    {
      digitalWrite(_pin, LOW);
    }
    else
    {
      Serial.println(F("Tidak Menerima Data"));
    }
  }
  else if (Firebase.getString(fbdo, pathDB))
  {
    getDataRelay::_get = fbdo.stringData();
    String res = getDataRelay::_get;
    res.replace('\"', ' ');
    dataRelay = res.toInt();
    if (dataRelay == 1)
    {
      digitalWrite(_pin, HIGH);
    }
    if (dataRelay == 0)
    {
      digitalWrite(_pin, LOW);
    }
  }
  else
  {
    Serial.println(fbdo.errorReason());
  }
  return dataRelay;
}

int getDataRelay::run(const char *pathDB, int &dataRelay, bool StateBuzzer)
{
  if (Firebase.getInt(fbdo, pathDB))
  {
    dataRelay = fbdo.intData();
    if (dataRelay == 1)
    {
      digitalWrite(_pin, HIGH);
    }
    else if (dataRelay == 0)
    {
      digitalWrite(_pin, LOW);
    }
    else
    {
      Serial.println(F("Tidak Menerima Data"));
    }
  }
  else if (Firebase.getString(fbdo, pathDB))
  {
    getDataRelay::_get = fbdo.stringData();
    String res = getDataRelay::_get;
    res.replace('\"', ' ');
    dataRelay = res.toInt();
    if (dataRelay = !dataRelay)
    {
      if (dataRelay == 1)
      {
        digitalWrite(_pin, HIGH);
      }
      if (dataRelay == 0)
      {
        digitalWrite(_pin, LOW);
      }
    }
    else if( dataRelay == dataRelay)
    {
      Serial.println("Data Sama");
    }
  }
  else
  {
    Serial.println(fbdo.errorReason());
  }
  return dataRelay;
}
