#include "OTA.h"
#include <Arduino.h>

OTA::OTA(Printer *printer_in)
  : printer(printer_in) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    printer->PrintMessage("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("timer");

  // No authentication by default
  ArduinoOTA.setPassword("admin");


  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([&]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      this->printer->PrintMessage("Start updating " + type);
    })
    .onEnd([&]() {
      this->printer->PrintMessage("\nEnd");
    })
    .onProgress([&](unsigned int progress, unsigned int total) {
      this->printer->PrintMessage("Progress: " + String((progress / (total / 100)), 4));
    })
    .onError([&](ota_error_t error) {
      this->printer->PrintMessage("Error[" + String(error) + "]: ");
      if (error == OTA_AUTH_ERROR) {
        this->printer->PrintMessage("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        this->printer->PrintMessage("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        this->printer->PrintMessage("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        this->printer->PrintMessage("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        this->printer->PrintMessage("End Failed");
      }
    });

  ArduinoOTA.begin();

  printer->PrintMessage("Ready");
  printer->PrintMessage("IP address: ");
  printer->PrintMessage(WiFi.localIP().toString());
}

void OTA::Handle() {
  ArduinoOTA.handle();
}