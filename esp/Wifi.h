#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>

class Wifi {
  public:
    void setup(String idRobo);
    void loop();
    String getServerIP();
    String getIP();
};

extern Wifi wifi; 

#endif
