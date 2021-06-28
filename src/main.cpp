#include <Arduino.h>
#include "Firebase.h"
#include "Connection.h"
#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "ThingSpeak.h"

#define buzzer D5

FB fb;                                //class object dari library firebase
Connection AT("b4871e", "277123586"); //SSID,PASS, Autoconnect Wifimanager WebServer jika lebih dari 5 Detik
getDataRelay GDR_1(16, buzzer);       // Data Relay True or False dari Firebase ke pin GPIO 16
getDataRelay GDR_2(00, buzzer);       // Data Relay True or False dari Firebase ke pin GPIO 0
DHT dht(12, DHT11);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
WiFiClient client;

int dataRelay_1;
int dataRelay_2;

float h;
float t;
String myStatus = "";

unsigned long myChannelNumber = xxxxxx;
const char *myWriteAPIKey = "xxxxxxxxxx";

byte Simbol_derajat = B11011111;

void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  AT.begin(buzzer);

  fb.begin("xxxxxxxxxxx.firebaseio.com", "xxxxxxxx4FFMg1H2"); // (Host Database Firebase, Auth Firebase)
  Firebase.reconnectWiFi(true);

  GDR_1.begin();
  GDR_2.begin();
  dht.begin();
  ThingSpeak.begin(client);

  pinMode(buzzer, OUTPUT);

  lcd.printS(0, 0, " Tersambung IP : ");
  lcd.setCursor(2, 1);
  lcd.print(WiFi.localIP());
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  lcd.clear();
}

void Relay_LCD(int dataInput, int num_Relay);
void main_LCD();
void processThingspeak();

void loop()
{
  GDR_1.run("/Relay_1", dataRelay_1, true);
  GDR_2.run("/Relay_2", dataRelay_2);

  h = dht.readHumidity();
  t = dht.readTemperature();

  main_LCD();

  fb.sendDataFloat(2000, "/Suhu", t);
  fb.sendDataInt(2000, "/Kelembapan", h);

  processThingspeak();
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

void processThingspeak()
{
  bool stateSend = false;
  unsigned long previousTime = 0;
  unsigned long Jeda = 20000;
  if (millis() >= previousTime + Jeda)
  {
    stateSend = !stateSend;
    if (stateSend)
    {
      ThingSpeak.setField(1, t);
      ThingSpeak.setField(2, h);
    }
    previousTime = millis();
  }

  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200)
  {
    Serial.println(F("Data Sudah Terkirim"));
  }
  else
  {
    Serial.println("Ada Masalah ketika Update. HTTP error code " + String(x));
  }
}