#include "Wifi.h"

Wifi::Wifi() {};

void Wifi::start() {
  WiFi.mode(WIFI_STA);

  wifi.addAP("STEM-MAKERSPACE", "St3mMK2k24!!");
  
  Serial.print("Conectando");

  while (wifi.run() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println();
  
  Serial.print("Conectado | Endereço IP:");
  Serial.println(WiFi.localIP());
};

Wifi::~Wifi() {};
