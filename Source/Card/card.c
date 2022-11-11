#include <stdio.h>
#include <string.h>

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8_t NameLength = strlen(cardData->cardHolderName);

    if ( NameLength < 20 || NameLength > 24 )
    {
        return WRONG_NAME;
    }

    for (int i=0;i < NameLength;i++)
    {
        if ((cardData->cardHolderName[i] < 'A' & cardData->cardHolderName[i]!=' ') || (cardData->cardHolderName[i] > 'z' ))
        {
            return WRONG_NAME;
        }
    }
    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t DateLength = strlen(cardData->cardExpirationDate);

    if( DateLength != 5 )
    {
        return WRONG_EXP_DATE;
    }

    if ((cardData->cardExpirationDate[4] >= '0' ) & (cardData->cardExpirationDate[4] <= '9' ))
    {
        if ((cardData->cardExpirationDate[3] >= '0' ) & (cardData->cardExpirationDate[3] <= '9' ))
        {
            if (cardData->cardExpirationDate[2]=='/')
            {
                if (cardData->cardExpirationDate[0]=='0')
                {
                    if ((cardData->cardExpirationDate[1] >= '0' ) & (cardData->cardExpirationDate[1] <= '9' ))
                    {
                        return CARD_OK;
                    }
                }
                else if (cardData->cardExpirationDate[0]=='1')
                {
                    if ((cardData->cardExpirationDate[1] >= '0' ) & (cardData->cardExpirationDate[1] <= '2' ))
                    {
                        return CARD_OK;
                    }
                }
            }
        }
    }    
    return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8_t PANLength = strlen(cardData->primaryAccountNumber);

    if( PANLength > 19 || PANLength < 16 )
    {
        return WRONG_PAN;
    }

    for (int i=0; i < PANLength ;i++)
    {
        if ((cardData->primaryAccountNumber[i] < '0' ) || (cardData->primaryAccountNumber[i] > '9' ))
        {
            return WRONG_PAN;
        }
    }
    return CARD_OK;
}

