#define BLYNK_PRINT Serial
#define fan 5
#define pompa 4
#define BLYNK_TEMPLATE_ID "TEMPLATE ID"
#define BLYNK_DEVICE_NAME "BitkiSulama"
#define BLYNK_AUTH_TOKEN "AUTH TOKEN"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "ThingSpeak.h"

char agAdi[] = "WIFI NAME";
char agSifre[] = "PASSWORD";
int deger ;
int nemOrani;
int nemSensor = A0;
int sulanacakNem;
int kurutulacakNem;
int otomatikButon;
int tweetButon;
int otomatikDurum;
int tweetDurum;

//
const String writeAPIKey = "WRITE API KEY";   // Thingspeak write API Key
char* thingSpeakHost = "api.thingspeak.com";     //ThingSpeak sitesinin hostu
String thingtweetAPIKey = "THINGTWEET API KEY";    //ThingTweet sayfasından aldığımız API Keyi
char thingSpeakAddress[] = "api.thingspeak.com";
String tsData;
int randNumber;
WiFiClient client;

//
BLYNK_WRITE(V2)
{
  sulanacakNem = param.asInt(); // Get value as integer
  Serial.print("Sulanacak Nem: ");
  Serial.println(sulanacakNem);
}
BLYNK_WRITE(V3)
{
  kurutulacakNem = param.asInt(); // Get value as integer
  Serial.print("Kurutulacak Nem: ");
  Serial.println(kurutulacakNem);
}

BLYNK_WRITE(V4)
{
  int otomatikButon = param.asInt();

  if (otomatikButon == 1) {
    otomatikDurum = 1;
  } else if (otomatikButon == 0) {
    otomatikDurum = 0;
    digitalWrite(fan, 1);//Devreye enerji verildiğinde kapalı başlaması için ayar
    digitalWrite(pompa, 1);//Devreye enerji verildiğinde kapalı başlaması için ayar
  }
}
BLYNK_WRITE(V5)
{
  tweetButon = param.asInt();
  Serial.print("Tweet Buton : ");
  Serial.println(tweetButon);
}
void setup() {
  digitalWrite(fan, 1);//Devreye enerji verildiğinde kapalı başlaması için ayar
  digitalWrite(pompa, 1);//Devreye enerji verildiğinde kapalı başlaması için ayar
  pinMode (A0, INPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, agAdi, agSifre);
}

void loop() {
  delay(500);
  deger = analogRead(nemSensor);//Nem sensöründen analog değer okuma
  Serial.print("Analog: ");
  Serial.println(deger);
  nemOrani = 100 - map(deger , 0, 1024, 0, 100);
  Serial.print("Yuzdelik: ");
  Serial.println(nemOrani);
  Blynk.virtualWrite(V1, nemOrani);
  Serial.print("TweetButon : ");
  Serial.println(tweetButon);

  randNumber = random(5, 1000);

  if (client.connect (thingSpeakHost, 80)) {        //Bu blokta sıcaklık değerini host urlsi yardımıyla ThingSpeak’e gönderiyoruz
    String postStr = "field1=";                  //1 Nolu Fielda verileri göstereceğiz
    postStr += String (nemOrani);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.print("\n\n");
    Serial.println ("Thingspeak'e nem degeri gönderildi");
  }

  if (tweetButon == 1) {
    if (client.connect("api.thingspeak.com", 80)) {
      Serial.println("TWİTTER BAĞLANTISI SAĞLANILDI");  //Tweet atılması için gereken blok
      tsData = "api_key=" + thingtweetAPIKey + "&status=" + "Nem Oranı  : " + nemOrani + "   // " + randNumber ;
      client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(tsData.length());
      client.print("\n\n");
      client.print(tsData);
      Serial.println("TWEET GÖNDERİLDİ");
      Blynk.logEvent("tweet_sent","Tweet gönderildi.");
      Blynk.virtualWrite(V5,0);
      tweetButon=0;
    }
  }

  if (otomatikDurum == 1) {
    if (nemOrani > kurutulacakNem ) {
      Serial.println("Kurutuluyor.");
      digitalWrite(fan , 0);// Fanı çalıştır.
      digitalWrite(pompa, 1);// Pompayı kapat.
    } else  if (nemOrani <= sulanacakNem) {
      Serial.println("Sulanıyor.");
      digitalWrite(fan , 1);// Fanı kapat.
      digitalWrite(pompa, 0);// Pompayı çalıştır.
    } else {
      digitalWrite(fan , 1);// Fanı kapat.
      digitalWrite(pompa, 1);// Pompayı kapat.
    }
  }
  client.stop();
  Blynk.run();
}