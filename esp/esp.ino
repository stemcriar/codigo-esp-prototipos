#include "Wifi.h"
#include "webSocketClient.h"
#include "serial_comm.h"

WifiController wifi;
Serial_comm arduino;

const String ip = "192.168.3.155";
const int port = 1801;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("\nStarting Esp");

  arduino.doHandshake("ESP", "OK", "ARD");

  String ID = arduino.getReceivedType();

  Serial.print("The type is: ");
  Serial.println(ID);
  setTypeToWs(ID);

  wifi.startWiFi(ID);
  wifi.startMDNS(ID);
  wifi.startWebServer(ID);

  arduino.sendJson("ESP_IP", wifi.ip);

  startWebSocketClient(ip, port);
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
