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

#define RELAY_TOGGLE_PIN 5 // D1 = GPIO 5

#define ALLOWED_CHIP_ID 2258390 //alowed chip ID

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen

long chipID;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // SPI-Verbindung aufbauen
  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers

  pinMode(RELAY_TOGGLE_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mfrc522.PICC_ReadCardSerial() && !mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  chipID = 0;
  // ChipID auslesen und in chipID speichern
  for (byte i = 0; i < mfrc522.uid.size; i++){
      chipID=((chipID+mfrc522.uid.uidByte[i])*10);
  }

  //Wenn richtige ID dann offne Relay für 5000ms => 5s
  if(access(chipID)){

    Serial.print("acces with: ");
    Serial.println(chipID);
    chipID = 0;
    openRelay(5000);

  } else {

    Serial.print("no access with: ");
    Serial.println(chipID);

  }
}

bool access(long id){
  return id == ALLOWED_CHIP_ID;
}

void openRelay(int duration){
  digitalWrite(RELAY_TOGGLE_PIN, HIGH);
  delay(duration);
  digitalWrite(RELAY_TOGGLE_PIN, LOW);
}
