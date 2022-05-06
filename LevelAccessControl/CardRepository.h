#ifndef CARD_REPOSITORY_H
#define CARD_REPOSITORY_H

#include <EEPROM.h>

#define CARD_CACHE_SIZE 100
#define CARD_REPOSITORY_EEPROM_START_ADDRESS 0
#define CARD_REPOSITORY_EEPROM_SIZE sizeof(t_cardRepositoryStorage)
#define CARD_REPOSITORY_MAGIC_IDENTIFIER 233456788;

typedef struct
{
  long identifier;
  long learnNewCardTrigger;
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
      EEPROM.begin(CARD_REPOSITORY_EEPROM_SIZE);

      populateFromEEprom();
      if (!isInitialized()) {
        initialize();
        storeToEEprom();
      }

      dumpLocalCardCacheToSerial();
    }

    bool isLearnNewCardTrigger(long cardUid) {
      return cardUid == localCardCache.learnNewCardTrigger;
    }

    bool hasCard(long cardUid) {
      for (int i = 0; i < CARD_CACHE_SIZE; i++) {
        if (cardUid == localCardCache.cardStorage[i]) {
          return true;
        }
      }

      return false;
    }

    bool addCard(long cardUid) {
      int freeSlotId = findFreeCardSlotId();

      if (freeSlotId >= CARD_CACHE_SIZE) {
        return false;
      }

      localCardCache.cardStorage[freeSlotId] = cardUid;
      storeToEEprom();

      return true;
    }

    bool dumpLocalCardCacheToSerial() {
      Serial.println("CardRepository.dumpLocalCache()");
      for(int i = 0; i < CARD_CACHE_SIZE; i++) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("] ");
        Serial.println(localCardCache.cardStorage[i]);
      }
    }

  private:
    bool isInitialized() {
      Serial.println("CardRepository.isInitialized()");
      return localCardCache.identifier == CARD_REPOSITORY_MAGIC_IDENTIFIER;
    }

    int findFreeCardSlotId() {
      Serial.println("CardRepository.findFreeCardSlotId()");
      for (int i = 0; i < CARD_CACHE_SIZE; i++) {
        if (localCardCache.cardStorage[i] == 0) {
          Serial.print("Found free slot: ");
          Serial.println(i);
          return i;
        }
      }

      return CARD_CACHE_SIZE;
    }

    void initialize() {
      Serial.println("CardRepository.initialize()");
      localCardCache.identifier = CARD_REPOSITORY_MAGIC_IDENTIFIER;
      for (int i = 0; i < CARD_CACHE_SIZE; i++) {
        localCardCache.cardStorage[i] = 0;
      }

      // fake rechner
      localCardCache.learnNewCardTrigger = CARD_REPOSITORY_LEARN_NEW_CARD_TRIGGER;
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
