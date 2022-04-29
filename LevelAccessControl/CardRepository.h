#ifndef CARD_REPOSITORY_H
#define CARD_REPOSITORY_H

#include <EEPROM.h>

#define CARD_CACHE_SIZE 100
#define CARD_REPOSITORY_EEPROM_START_ADDRESS 0
#define CARD_REPOSITORY_EEPROM_SIZE sizeof(t_cardRepositoryStorage)
#define CARD_REPOSITORY_MAGIC_IDENTIFIER 123456778;

typedef struct
{
  long identifier;
  long cardStorage[CARD_CACHE_SIZE];
  long checksum;
} t_cardRepositoryStorage;

class CardRepository
{
  private:
    t_cardRepositoryStorage localCardCache;

  public:
    CardRepository() {}

    void begin() {
      Serial.print("CardRepository.begin() EEPROM size = ");
      Serial.println(CARD_REPOSITORY_EEPROM_SIZE);
      EEPROM.begin(CARD_REPOSITORY_EEPROM_SIZE);

      populateFromEEprom();
      if (!isInitialized()) {
        initialize();
        storeToEEprom();
      }
    }

    bool isValidCard(long cardId) {
      return cardId == CARD_REPOSITORY_ALLOWED_CARD_ID;
    }

    bool dumpLocalCardCacheToSerial() {
      Serial.println("CardRepository.dumpLocalCache()");
      for(int i = 0; i < CARD_CACHE_SIZE; i++) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("] 0x");
        Serial.println(localCardCache.cardStorage[i], HEX);
      }
    }

  private:
    bool isInitialized() {
      Serial.println("CardRepository.isInitialized()");
      return localCardCache.identifier == CARD_REPOSITORY_MAGIC_IDENTIFIER;
    }

    void initialize() {
      Serial.println("CardRepository.initialize()");
      localCardCache.identifier = CARD_REPOSITORY_MAGIC_IDENTIFIER;
      for (int i = 0; i < CARD_CACHE_SIZE; i++) {
        localCardCache.cardStorage[i] = 0;
      }

      // fake first valid card
       localCardCache.cardStorage[0] = CARD_REPOSITORY_ALLOWED_CARD_ID;
    }

    void populateFromEEprom() {
      EEPROM.get(CARD_REPOSITORY_EEPROM_START_ADDRESS, localCardCache);
    }

    void storeToEEprom() {
      Serial.println("CardRepository.storeToEEprom()");

      EEPROM.put(CARD_REPOSITORY_EEPROM_START_ADDRESS, localCardCache);
      EEPROM.commit();
    }
};

#endif // CARD_REPOSITORY_H
