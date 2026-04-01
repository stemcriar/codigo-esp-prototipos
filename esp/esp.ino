#include "Wifi.h"
#include "webSocketClient.h"
#include "serial_comm.h"

WifiController wifi;
Serial_comm arduino;

// id único do protótipo, deve ser o mesmo do adesivo
const String id = "CAR001"; 

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

  wifi.startWiFi(id);
  wifi.startMDNS(id);
  wifi.startWebServer(id);

  wifi.loadServerIP();
  Serial.print("IP do Servidor Carregado da Memoria: ");
  Serial.println(wifi.serverIP);

  arduino.sendJson("ESP_IP", wifi.ip);

  startWebSocketClient(wifi.serverIP, 1801);
  arduino.sendJson("ws_client", "started");
  updateWebsocketClient();
  Serial.println("End of Setup");
};

void loop()
{
  wifi.updateMDNS();
  wifi.handleWebServer();

  updateWebsocketClient();
  arduino.getJson();
  if (arduino.jsonUpdateCheck())
  {
    arduino.serializeCurrentJson();
    sendMessageWsClient(arduino.serializedCurrentJson);
  };
};
