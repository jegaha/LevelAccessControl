#define RELAY_TOGGLE_PIN 'D1' // pin 'D1' or GPIO 5

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

long chipID;

void setup() {
  Serial.begin(9600);

  // setupRelay();
  setupRfidReceiver();
}

void setupRelay() {
  pinMode(RELAY_TOGGLE_PIN, OUTPUT); // Set pin as output
}

void setupRfidReceiver(){
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // loopRelay();
  loopRfidReceiver();
}

void loopRelay() {
  digitalWrite(RELAY_TOGGLE_PIN, HIGH); // Turn pin on
  delay(1000);
  digitalWrite(RELAY_TOGGLE_PIN, LOW); // Turn pin off
  delay(1000);
}

void loopRfidReceiver(){
  if(!mfrc522.PICC_ReadCardSerial() && !mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  chipID = 0;
  // ChipID auslesen und in chipID speichern
  for (byte i = 0; i < mfrc522.uid.size; i++){
      chipID=((chipID+mfrc522.uid.uidByte[i])*10);
  }
  Serial.println(chipID);
}
