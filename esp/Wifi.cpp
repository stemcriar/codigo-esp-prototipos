#include "Wifi.h"

WifiController::WifiController() : server(80) {};

WifiController::~WifiController() { /* ¯\_(ツ)_/¯ */ }; // Destructor

void WifiController::startWiFi(String ID)
{
  Serial.println("\n\rConnecting");
  WiFiManager wifiManager;

  String apName = "Config-ESP-" + ID;

  delay(500);
  if (!wifiManager.autoConnect(apName.c_str())) {
    Serial.println("Falha ao ligar. A reiniciar...");
    ESP.restart();
    delay(1000);
  }

  Serial.print("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID()); // Nome da rede
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP()); // Ip do esp na rede local

  this->ip = WiFi.localIP().toString().c_str();

  Serial.println("\r\n");
};

void WifiController::startMDNS(String mdnsName)
{ // Iniciar o mDNS com o nome desejado para a rede .local

  MDNS.begin(mdnsName); // começa a transmissão do nome
  if (!MDNS.begin(mdnsName))
  {
    Serial.println("Error setting up MDNS responder!");
  }
  MDNS.addService("ws", "tcp", 81);
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
};

void WifiController::updateMDNS()
{
  MDNS.update();
};

void WifiController::startWebServer(String id) 
{
  this->carID = id;

  // Usamos uma função lambda [this]() para podermos aceder ao this->carID facilmente
  server.on("/", [this]() {
    String html = "<html><head><meta charset='UTF-8'></head>";
    html += "<body style='display: flex; justify-content: center; align-items: center; height: 100vh; font-family: sans-serif;'>";
    html += "<h1>Você está vendo o carrinho " + this->carID + "</h1>";
    html += "</body></html>";
    
    this->server.send(200, "text/html", html);
  });

  server.begin();
  Serial.println("Servidor Web iniciado!");
}

void WifiController::handleWebServer() 
{
  server.handleClient();
}