#include <SoftwareSerial.h>

#ifndef Esp8266_HTTP_H
#define Esp8266_HTTP_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
class SoftwareSerial;
class Esp
{
private:
  SoftwareSerial EspSerial;

public:
  Esp(uint8_t rx, uint8_t tx) : EspSerial(rx, tx){};
  char read();
  void begin(uint32_t baund = 115200);
  void listen();
  boolean available();
  boolean ready();
  boolean clientMode();
  boolean connect(String ssid, String pass);
  boolean startHttp(String ip, String port);
  boolean http(String uri, String method);
  boolean closeHttp();
};
#endif
