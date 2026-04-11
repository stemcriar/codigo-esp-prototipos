#include "Wifi.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <EEPROM.h>

Wifi wifi; // Instância global

// Variáveis Globais internas do módulo
WiFiManager wm;
char ipServidor[40] = "";
WiFiManagerParameter custom_server_ip("server", "IP do Servidor STEM Criar", ipServidor, 40);

// Função Callback (Chamada quando o usuário clica em "Salvar" na página web)
void callbackSalvarConfig() {
  Serial.println("Nova configuracao detectada pelo Portal Web.");
  
  // Atualiza a variável e salva na memória permanente
  strncpy(ipServidor, custom_server_ip.getValue(), sizeof(ipServidor));
  
  EEPROM.begin(512);
  EEPROM.put(0, ipServidor);
  EEPROM.commit();
  EEPROM.end();
  
  Serial.print("Novo IP do Servidor Salvo: ");
  Serial.println(ipServidor);
}

void Wifi::setup(String idRobo) {
  // 1. Lê a memória EEPROM ao ligar
  EEPROM.begin(512); 
  EEPROM.get(0, ipServidor); 
  ipServidor[39] = '\0'; // Garante o final da string
  EEPROM.end();

  // 2. Configurações do WiFiManager (Menu, OTA e Callbacks)
  std::vector<const char *> menu = {"wifi", "param", "info", "update", "restart"};
  wm.setMenu(menu);
  wm.setSaveConfigCallback(callbackSalvarConfig);
  wm.setSaveParamsCallback(callbackSalvarConfig); 
  wm.setHostname(idRobo.c_str()); 
  
  // Injeta o campo customizado com o valor atual
  custom_server_ip.setValue(ipServidor, 40);
  wm.addParameter(&custom_server_ip);

  // 3. Tenta conectar ou cria a rede AP (Config-ESP-ID)
  String nomeRedeConfig = "Config-ESP-" + idRobo;
  if(!wm.autoConnect(nomeRedeConfig.c_str())) {
    Serial.println("Falha ao conectar. Reiniciando...");
    ESP.restart();
  }

  Serial.println("Conectado ao Wi-Fi!");

  // 4. Inicia o mDNS (.local)
  if (MDNS.begin(idRobo.c_str())) {
    Serial.print("mDNS iniciado! Acesse: http://");
    Serial.print(idRobo);
    Serial.println(".local");
  }

  // 5. Inicia o Portal em segundo plano (Modo Estação)
  wm.startWebPortal();
  Serial.println("Portal web de configuracao rodando em segundo plano.");

  Serial.print("IP carregado da EEPROM: ");
  Serial.println(ipServidor);
}

void Wifi::loop() {
  // Mantém o portal e o mDNS respondendo sem travar o Arduino
  wm.process();
  MDNS.update();
}

String Wifi::getServerIP() {
  return String(ipServidor);
}

String Wifi::getIP() {
  return WiFi.localIP().toString();
}
