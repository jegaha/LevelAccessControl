#ifndef STA_SERVER_H
#define STA_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class StaServer
{
  private:
    ESP8266WebServer* server = NULL;
    bool isEnabled = false;

  public:
    StaServer() {
    }

    void enable() {
      if (isEnabled) {
        return;
      }
      enableAP();
      startWebServer();
      isEnabled = true;
    }

    void disable() {
      if (!isEnabled) {
        return;
      }

      stopWebserver();
      disableAP();
      isEnabled = false;
    }

    void loop() {
      if (server) {
        server->handleClient();
      }
    }

    void handleRoot() {
      server->send(200, "text/plain", "hello from esp8266!");
    }

    void handleNotFound() {
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server->uri();
      message += "\nMethod: ";
      message += (server->method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server->args();
      message += "\n";
      for (uint8_t i = 0; i < server->args(); i++) {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
      }
      server->send(404, "text/plain", message);
    }

  private:
    void enableAP() {
      Serial.println("StaServer.enableAP()");
      WiFi.softAP(AP_SSID, AP_PASS);
      Serial.print("IP address for STA network ");
      Serial.print(AP_SSID);
      Serial.print(" : ");
      Serial.print(WiFi.softAPIP());
    }

    void disableAP() {
      Serial.println("StaServer.disableAP()");
      WiFi.softAPdisconnect(true);
    }

    void startWebServer() {
      Serial.println("StaServer.startWebServer()");
      server = new ESP8266WebServer(80);
      server->on("/", std::bind(&StaServer::handleRoot, this));
      server->onNotFound(std::bind(&StaServer::handleNotFound, this));
      server->begin();
    }

    void stopWebserver() {
      Serial.println("StaServer.stopWebServer()");
      server->close();
      delete(server);
      server = NULL;
    }
};

#endif // STA_SERVER_H
