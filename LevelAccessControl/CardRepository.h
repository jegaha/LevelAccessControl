#ifndef CARD_REPOSITORY_H
#define CARD_REPOSITORY_H

class CardRepository
{
  public:
    CardRepository() {}

    bool isValidCard(long cardId) {
      return cardId == CARD_REPOSITORY_ALLOWED_CARD_ID;
    }
};

#endif // CARD_REPOSITORY_H
