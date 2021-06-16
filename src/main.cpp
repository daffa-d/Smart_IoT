#include <Arduino.h>
#include "Firebase.h"
#include "Connection.h"
#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "ThingSpeak.h"

FB fb;                                //class object dari library firebase
Connection AT("b4871e", "**********"); //SSID,PASS, Autoconnect Wifimanager WebServer jika lebih dari 5 Detik
getDataRelay GDR_1(16);               // Data Relay True or False dari Firebase ke pin GPIO 16
getDataRelay GDR_2(00);               // Data Relay True or False dari Firebase ke pin GPIO 0
DHT dht(12, DHT11);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
WiFiClient client;

int dataRelay_1;
int dataRelay_2;
float h;
float t;
String myStatus = "";

unsigned long myChannelNumber = *********;
const char *myWriteAPIKey = "*************";

byte Simbol_derajat = B11011111;

void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  AT.begin();

  fb.begin("***************", "****************"); // (Host Database Firebase, Auth Firebase)
  Firebase.reconnectWiFi(true);

  GDR_1.begin();
  GDR_2.begin();
  dht.begin();
  ThingSpeak.begin(client);

  lcd.printS(0, 0, " Tersambung IP : ");
  lcd.setCursor(2, 1);
  lcd.print(WiFi.localIP());
  delay(5000);
  lcd.clear();
}

void Relay_LCD(int dataInput, int num_Relay);
void main_LCD();
void processing();

void loop()
{

  GDR_1.getData_Relay("/Relay_1", dataRelay_1);
  GDR_2.getData_Relay("/Relay_2", dataRelay_2);

  h = dht.readHumidity();
  t = dht.readTemperature();

  main_LCD();

  fb.sendDataFloat(2000, "/Suhu", t);
  fb.sendDataFloat(2000, "/Kelembapan", h);

  uint32_t previousTime = 0;
  int Jeda = 20000;
  unsigned long now = millis();
  if (now - previousTime >= Jeda)
  {
    previousTime = now;
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    processing();
  }
}

void main_LCD()
{
  lcd.printS(1, 1, "Suhu : ");
  lcd.print(t);
  lcd.write(Simbol_derajat);
  lcd.println("C ");

  lcd.printS(0, 0, "Kelembapan : ");
  int hd = (int)h;
  lcd.print(hd);
  lcd.print("% ");

  /*
  uint32_t Previous_t = 0;
  int Jeda = 5000;
  unsigned long Run = millis();
  if(Run - Previous_t >= Jeda)
  {
    lcd.clear();
    Previous_t = Run;
    lcd.printS(0, 0, "Relay 1");
    if(dataRelay_1 == 1){
      lcd.printS(9, 0, "Aktif");
      lcd.clear();
    }
    else if(dataRelay_1 == 0){
      lcd.printS(9, 0, "Nonaktif");
      lcd.clear();
    }
  }
  */
}

void Relay_LCD(int dataInput, int num_Relay)
{
  if (dataInput == 1)
  {
    lcd.printS(3, 0, "Relay ke ");
    lcd.print(num_Relay);
    lcd.printS(2, 1, "Nonaktif");
    delay(2000);
    lcd.clear();
  }
  else if (dataInput == 0)
  {
    lcd.printS(3, 0, "Relay ke ");
    lcd.print(num_Relay);
    lcd.printS(2, 1, "Aktif");
    delay(2000);
    lcd.clear();
  }
}

void processing()
{
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200)
  {
    Serial.println("Data Sudah Terkirim");
  }
  else
  {
    Serial.println("Ada Masalah ketika Update. HTTP error code " + String(x));
  }
}