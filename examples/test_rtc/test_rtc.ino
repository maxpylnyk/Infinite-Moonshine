/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

void setup()
{
  Serial.begin(9600);
  clock.begin();
  //clock.setDateTime(__DATE__, __TIME__);
}

void loop() {
  //Serial.println(getTimeStamp());

  dt = clock.getDateTime();
  Serial.println(dt.unixtime);
  delay(1000);
}

String getTimeStamp() {
  dt = clock.getDateTime();
  String out = String(dt.year);
  out += "-" + String(dt.month / 10) + String(dt.month % 10);
  out += "-" + String(dt.day / 10) + String(dt.day % 10);
  out += " " + String(dt.hour / 10) + String(dt.hour % 10);
  out += ":" + String(dt.minute / 10) + String(dt.minute % 10);
  out += ":" + String(dt.second / 10) + String(dt.second % 10);
  return out;
}
