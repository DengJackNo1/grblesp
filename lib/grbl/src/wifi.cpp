/*
  wifi.cpp - Handles connection to wifi and makes web, websockets and telnet
  connections available
*/

#include <ESP8266WiFi.h>
#include "report.hpp"
#include "config.hpp"
#include "cpu_map.hpp"
#ifdef ENABLE_mDNS
#include <ESP8266mDNS.h>
#endif
#ifdef ENABLE_WEBSOCKET
#include "websocket.hpp"
#include "serial2socket.hpp"
#endif
#ifdef ENABLE_TELNET
#include "telnet_server.hpp"
#endif
#ifdef ENABLE_OTA
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#endif

void wifi_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  // Serial.print("\n[Connected: ");
  // Serial.print(WiFi.localIP());
  // Serial.println("]");

#ifdef ENABLE_mDNS
  MDNS.begin(WIFI_HOSTNAME); // {WIFI_HOSTNAME}.local
  MDNS.enableArduino(8266); // 不用加 .local 的域名了
#endif

#ifdef ENABLE_TELNET
  telnetServer.begin();
#endif
#ifdef ENABLE_WEBSOCKET
  websocket_init();
#endif
#ifdef ENABLE_OTA
  ArduinoOTA.setHostname(OTA_HOSTNAME); //上传窗口名字
  ArduinoOTA.setPassword(OTA_HOSTNAME); //上传密码，防止随便上传
  ArduinoOTA.begin();
#endif
  // be sure we are not is mixed mode in setup
  // WiFi.scanNetworks(true);
}

void wifi_handle()
{
  // if (WiFi.getMode() == WIFI_AP_STA)
  // {
  //   if (WiFi.scanComplete() != WIFI_SCAN_RUNNING)
  //   {
  //     WiFi.enableSTA(false);
  //   }
  // }
#ifdef ENABLE_HTTP
  web_server.handle();
#endif
}

void wifi_loop()
{
#ifdef ENABLE_OTA
  ArduinoOTA.handle();
#endif
#ifdef ENABLE_mDNS
  MDNS.update();
#endif
}
