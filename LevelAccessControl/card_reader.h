#ifndef CARD_READER_H
#define CARD_READER_H

#include <SPI.h>
#include <MFRC522.h>

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

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Receiver instance

void setupRfidReceiver(){
  SPI.begin();
  mfrc522.PCD_Init();
}

void loopRfidReceiver(){
  if(!mfrc522.PICC_ReadCardSerial() && !mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  long chipID = 0;
  // ChipID auslesen und in chipID speichern
  for (byte i = 0; i < mfrc522.uid.size; i++){
      chipID=((chipID+mfrc522.uid.uidByte[i])*10);
  }
  Serial.println(chipID);
}

#endif // CARD_READER_H
