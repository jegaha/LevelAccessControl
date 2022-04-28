#include <SPI.h>
#include <MFRC522.h>

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "credentials.h"

/*
*
* PINOUT:
*
* RFID-Reader | D1 Mini
*    RST      |  D3
*    SDA      |  D8    (SPI SS)
*   MOSI      |  D7    (SPI MOSI)
*   MISO      |  D6    (SPI MISO)
*    SCK      |  D5    (SPI SCK)
*   3.3V      |  3v3
*    GND      |  G
*/


#define SS_PIN 15 // D8 = GPIO 15 
#define RST_PIN 0 // D3 = GPIO 0

#define RELAY_TOGGLE_PIN 5 // D1 = GPIO 5

#define ALLOWED_CHIP_ID 2258390UL //alowed chip ID

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen



void setup() {
  Serial.begin(9600);
  Serial.printf("Try to connect to WiFi: ");
  Serial.println(ssid);
  Serial.println("Begin OTA setup..");
  OTAsetup();


//  ESP.wdtDisable();

  SPI.begin(); // SPI-Verbindung aufbauen
  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers

  pinMode(RELAY_TOGGLE_PIN, OUTPUT);
}

bool relayTriggered = false;
unsigned long relayOpenUntil = 0;

void loop() {
  long chipId;

  ArduinoOTA.handle();
  
  chipId = handleCardReader();

  handleChipId(chipId);

  handleRelais();
}

void handleChipId(long chipId) {
  if (chipId) {
    Serial.print("card ID: ");
    Serial.println(chipId);

    if(access(chipId)){

      Serial.print("access with: ");
      Serial.println(chipId);

      triggerRelay();

    } else {

      Serial.print("no access with: ");
      Serial.println(chipId);

    }
  }
}

bool access(long id){
  return id == ALLOWED_CHIP_ID;
}

void triggerRelay(){
  if (!relayOpenUntil) {
    relayTriggered = true;
  }
}

void handleRelais(){

  if (relayTriggered)
  {
    relayOpenUntil = millis() + 2500;

    if (relayOpenUntil == 0) {
      relayOpenUntil = 1;
    }

    digitalWrite(RELAY_TOGGLE_PIN, HIGH);
    relayTriggered = false;
  }

  if (relayOpenUntil && (millis() > relayOpenUntil)) {
    digitalWrite(RELAY_TOGGLE_PIN, LOW);
    relayOpenUntil = 0;
  }


}
int handleCardReader() {
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return NULL;
  }

  if (!mfrc522.PICC_ReadCardSerial())
  {
    return NULL;
  }
  
  return readChipId();
}

long readChipId(){
  long chipId = 0;
  // ChipID auslesen und in chipId speichern
  for (byte i = 0; i < mfrc522.uid.size; i++){
      chipId=((chipId+mfrc522.uid.uidByte[i])*10);
  }
  return chipId;
}



//OTA-Stuff:

void OTAsetup(){
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("ELEVATOR");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}


