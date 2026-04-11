#include "Wifi.h"
#include "webSocketClient.h"
#include "serial_comm.h"

Serial_comm arduino;

// id único do protótipo, deve ser o mesmo do adesivo
const String id = "STEM013";

void setup() 
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("\nStarting Esp");

  arduino.doHandshake("ESP", "OK", "ARD");
  
  String type = arduino.getReceivedType();
  Serial.print("The type is: ");
  Serial.println(type);
  setTypeToWs(type);
  setEspNameToWs(id); 

  wifi.setup(id);

  String ipDaESP = wifi.getIP();
  String ipDoServidor = wifi.getServerIP();
  
  arduino.sendJson("ESP_IP", ipDaESP.c_str());

  startWebSocketClient(ipDoServidor, 1801);
  arduino.sendJson("ws_client", "started");
  updateWebsocketClient();
  Serial.println("End of Setup");
};

void loop() 
{
  wifi.loop();

  updateWebsocketClient();
  arduino.getJson();
  if (arduino.jsonUpdateCheck())
  {
    arduino.serializeCurrentJson();
    sendMessageWsClient(arduino.serializedCurrentJson);
  };
};
