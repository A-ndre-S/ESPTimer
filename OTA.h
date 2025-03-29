#pragma once
#include <WiFi.h>
#include <ESPmDNS.h>
#include <NetworkUdp.h>
#include <ArduinoOTA.h>
#include "Printer.h"

class OTA {
public:

  OTA(Printer *printer);

  void Handle();

private:
  Printer *const printer;
  const char *ssid = "YourSSID";
  const char *password = "YourPassword";
};