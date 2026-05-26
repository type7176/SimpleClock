#include <Arduino.h>
#include <Wire.h>
#include <ESP8266_LCD_1602_RUS.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

LCD_1602_RUS lcd(0x27, 16, 2);

const char* ssid = "Имя сети";
const char* password = "Пароль сети";
const char* mqtt_server = "Адрес брокера";
const int mqtt_port = Порт брокера;
const char* mqtt_user = "Пользователь брокера";
const char* mqtt_password = "Пароль пользователя";
const char* mqtt_topic = "clock/display";

WiFiClient espClient;
PubSubClient client(espClient);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800, 3600000);

bool displayOn = true;
int lastHour = -1;
int lastMinute = -1;

int xtime = 0;
int ytime = 0;
int ntime = 0;
int mtime = 0;
int r1time = 0;
int r2time = 0;
int r3time = 0;
int r4time = 0;

byte customChar6[] = { B00000, B00000, B00000, B00001, B00001, B00000, B00000, B00000 };
byte customChar7[] = { B00000, B00000, B00000, B10000, B10000, B00000, B00000, B00000 };
byte customChar1[] = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte customChar2[] = { B11111, B11111, B00000, B00000, B00000, B00000, B00000, B00000 };
byte customChar3[] = { B00000, B00000, B00000, B00000, B00000, B00000, B11111, B11111 };
byte customChar4[] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte customChar5[] = { B11111, B11111, B00000, B00000, B00000, B00000, B11111, B11111 };

void x0() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(2, customChar2); lcd.setCursor((xtime + 1), 0); lcd.write(2);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 1); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x1() {
    lcd.createChar(2, customChar2); lcd.setCursor(xtime, 0); lcd.write(2);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 1), 0); lcd.write(1);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 2), 0); lcd.write(4);
    lcd.createChar(3, customChar3); lcd.setCursor(xtime, 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 1), 1); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 2), 1); lcd.write(3);
}

void x2() {
    lcd.createChar(2, customChar2); lcd.setCursor(xtime, 0); lcd.write(2);
    lcd.createChar(2, customChar2); lcd.setCursor((xtime + 1), 0); lcd.write(2);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 1); lcd.write(1);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 1); lcd.write(5);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 2), 1); lcd.write(3);
}

void x3() {
    lcd.createChar(2, customChar2); lcd.setCursor(xtime, 0); lcd.write(2);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 0); lcd.write(5);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor(xtime, 1); lcd.write(3);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x4() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 1), 0); lcd.write(4);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(2, customChar2); lcd.setCursor(xtime, 1); lcd.write(2);
    lcd.createChar(2, customChar2); lcd.setCursor((xtime + 1), 1); lcd.write(2);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x5() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 0); lcd.write(5);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 2), 0); lcd.write(5);
    lcd.createChar(3, customChar3); lcd.setCursor(xtime, 1); lcd.write(3);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x6() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 0); lcd.write(5);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 2), 0); lcd.write(5);
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 1); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x7() {
    lcd.createChar(2, customChar2); lcd.setCursor(xtime, 0); lcd.write(2);
    lcd.createChar(2, customChar2); lcd.setCursor((xtime + 1), 0); lcd.write(2);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(4, customChar4); lcd.setCursor(xtime, 1); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 1), 1); lcd.write(4);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x8() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 0); lcd.write(5);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 1); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x9() {
    lcd.createChar(1, customChar1); lcd.setCursor(xtime, 0); lcd.write(1);
    lcd.createChar(5, customChar5); lcd.setCursor((xtime + 1), 0); lcd.write(5);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 0); lcd.write(1);
    lcd.createChar(3, customChar3); lcd.setCursor(xtime, 1); lcd.write(3);
    lcd.createChar(3, customChar3); lcd.setCursor((xtime + 1), 1); lcd.write(3);
    lcd.createChar(1, customChar1); lcd.setCursor((xtime + 2), 1); lcd.write(1);
}

void x10() {
    lcd.createChar(4, customChar4); lcd.setCursor(xtime, 0); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 1), 0); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 2), 0); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor(xtime, 1); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 1), 1); lcd.write(4);
    lcd.createChar(4, customChar4); lcd.setCursor((xtime + 2), 1); lcd.write(4);
}

void n() {
    if (ytime == 0) { x0(); }
    if (ytime == 1) { x1(); }
    if (ytime == 2) { x2(); }
    if (ytime == 3) { x3(); }
    if (ytime == 4) { x4(); }
    if (ytime == 5) { x5(); }
    if (ytime == 6) { x6(); }
    if (ytime == 7) { x7(); }
    if (ytime == 8) { x8(); }
    if (ytime == 9) { x9(); }
    if (ytime == 10) { x10(); }
}

void NB1() {
    if (ntime >= 10 & ntime < 100) {
        xtime = 0; r3time = ntime / 10; ytime = r3time; n();
        xtime = 4; r4time = ntime - r3time * 10; ytime = r4time; n();
    }
    if (ntime >= 0 & ntime < 10) {
        xtime = 0; ytime = 10; n();
        xtime = 4; r4time = ntime; ytime = r4time; n();
    }
}

void NB2() {
    if (mtime >= 10 & mtime < 100) {
        xtime = 9; r3time = mtime / 10; ytime = r3time; n();
        xtime = 13; r4time = mtime - r3time * 10; ytime = r4time; n();
    }
    if (mtime >= 0 & mtime < 10) {
        xtime = 9; ytime = 0; n();
        xtime = 13; r4time = mtime; ytime = r4time; n();
    }
}

void drawColon() {
    lcd.createChar(6, customChar6); lcd.setCursor(7, 0); lcd.write(6);
    lcd.createChar(7, customChar7); lcd.setCursor(8, 0); lcd.write(7);
    lcd.createChar(6, customChar6); lcd.setCursor(7, 1); lcd.write(6);
    lcd.createChar(7, customChar7); lcd.setCursor(8, 1); lcd.write(7);
}

void displayTime(int hour, int minute) {
    ntime = hour;
    mtime = minute;
    NB1();
    NB2();
    drawColon();
}

void forceDisplayUpdate() {
    timeClient.update();
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    lastHour = currentHour;
    lastMinute = currentMinute;
    lcd.clear();
    displayTime(currentHour, currentMinute);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    if (message == "1") {
        displayOn = true;
        lcd.backlight();
        forceDisplayUpdate();
    } else if (message == "0") {
        displayOn = false;
        lcd.clear();
        lcd.noBacklight();
    }
}

void reconnect() {
    while (!client.connected()) {
        if (client.connect("ESP32Clock", mqtt_user, mqtt_password)) {
            client.subscribe(mqtt_topic);
        } else {
            delay(5000);
        }
    }
}

void setup() {
    lcd.init();
    lcd.backlight();
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    
    timeClient.begin();
    timeClient.update();
    
    forceDisplayUpdate();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    
    if (displayOn) {
        static unsigned long lastNTPUpdate = 0;
        unsigned long now = millis();
        
        if (now - lastNTPUpdate > 60000) {
            timeClient.update();
            lastNTPUpdate = now;
        }
        
        int currentHour = timeClient.getHours();
        int currentMinute = timeClient.getMinutes();
        
        if (currentHour != lastHour || currentMinute != lastMinute) {
            lastHour = currentHour;
            lastMinute = currentMinute;
            lcd.clear();
            displayTime(currentHour, currentMinute);
        }
    }
    
    delay(100);
}