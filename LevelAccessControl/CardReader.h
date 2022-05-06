#ifndef CARD_READER_H
#define CARD_READER_H

#include <SPI.h>
#include <MFRC522.h>

class CardReader
{
  private:
    MFRC522 mfrc522;

  public:
    CardReader(int ss_pin, int rst_pin)
      : mfrc522(ss_pin, rst_pin)
    {}

    void begin() {
      SPI.begin();
      this->mfrc522.PCD_Init();
    }

    unsigned long getCardId() {
      if((mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) == false) {
        return NULL;
      }

      unsigned long cardUid = 0;
      for (byte i = 0; i < mfrc522.uid.size; i++){
          cardUid = cardUid << 8;
          cardUid = cardUid + mfrc522.uid.uidByte[i];
      }
      return cardUid;
    }
};

#endif // CARD_READER_H
