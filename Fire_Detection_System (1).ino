#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid =  "Akshara";
const char *pass =  "venkat5577";

//#define BOTtoken "7088058754:AAFUA-t-jrDi_P5zxPoZEV8RuK3jXUrqR_A"
//#define CHAT_ID "1731615737"
//
//#ifdef ESP8266
//X509List cert(TELEGRAM_CERTIFICATE_ROOT);
//#endif
//
//WiFiClientSecure client;
//UniversalTelegramBot bot(BOTtoken, client);
//
//int botRequestDelay = 1000;
//unsigned long lastTimeBotRan;

const int buz = D8;
const int relay = D4;
const int gasSensor = D5;

const int in1 = D6;
const int in2 = D7;

void setup()
{
  pinMode(gasSensor, INPUT);
  pinMode(buz, OUTPUT); digitalWrite(buz, LOW);
  pinMode(relay, OUTPUT); digitalWrite(relay, HIGH);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  digitalWrite(in1, HIGH);  digitalWrite(in2, HIGH);
  //  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  //  client.setTrustAnchors(&cert);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Gas Leakage");
  lcd.setCursor(0, 1);
  lcd.print("Detection System");
  delay(1500);
  lcd.clear();
  lcd.print(" IOT and NodeMCU");
  delay(1500);
  //  lcd.clear();
  //  lcd.print("Connecting with ");
  //  lcd.setCursor(0, 1);
  //  lcd.print(ssid);
  //  delay(1500);
  //
  //  WiFi.begin(ssid, pass);
  //
  //  while (WiFi.status() != WL_CONNECTED)
  //  {
  //    delay(500);
  //  }
  //  lcd.clear();
  //  lcd.print("Wi-Fi Connected");
  //  //  bot.sendMessage(CHAT_ID, "WiFi Connected Successfully..", "");
  //  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  //  delay(1000);
}

void loop()
{
  int pos;
  int gas = digitalRead(gasSensor);
  lcd.clear();  lcd.print("Gas:"); lcd.print(gas);
  delay(800);

  if (gas == LOW)
  {
    digitalWrite(buz, HIGH);  digitalWrite(relay, LOW);
    digitalWrite(in1, HIGH);  digitalWrite(in2, LOW);
    lcd.clear();
    lcd.print(" Gas Detected ");
    lcd.setCursor(0, 1);
    lcd.print("***Buzzer ON****");
    delay(1500);
    //bot.sendMessage(CHAT_ID, "Gas Deteced at Kitchen", "");1
    digitalWrite(buz, LOW);   digitalWrite(relay, HIGH);
    digitalWrite(in1, HIGH);  digitalWrite(in2, HIGH);
    delay(1000);
  }
  else
  {
    lcd.clear();
    lcd.print("No Gas");
    lcd.setCursor(6, 1);
    lcd.print("Detected");
    digitalWrite(buz, LOW);  digitalWrite(in1, HIGH);  digitalWrite(in2, HIGH);
    delay(500);
  }
}
