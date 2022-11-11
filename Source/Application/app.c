
#include "app.h"
#include "../Card/card.c"
#include "../Terminal/terminal.c"
#include "../Server/server.c"

void appStart(void)
{
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_accountsDB_t account; 

    // Card Data
    strcpy(card.cardHolderName, "Islam Mohamed Barakat");
    strcpy(card.cardExpirationDate,"05/23");
    strcpy(card.primaryAccountNumber,"123456789123456789");
    // Terminal Data
    terminal.transAmount= 200.0;
    terminal.maxTransAmount= 4000.0;
    getTransactionDate(&terminal);

    if(getCardHolderName(&card)== CARD_OK && getCardExpiryDate(&card)== CARD_OK && getCardPAN(&card) == CARD_OK)
    {
        if(isCardExpired(&card, &terminal) == EXPIRED_CARD)
        {
            printf("%s","Declined Expired Card!");
            return;
        }
        else if (isBelowMaxAmount(&terminal) == EXCEED_MAX_AMOUNT)
        {
            printf("%s","Declined Amount Exceeding Limit!");
            return;
        }
        else
        {
            ST_transaction_t transData;
            // Card Data
            strcpy(transData.cardHolderData.cardHolderName, card.cardHolderName);
            strcpy(transData.cardHolderData.cardExpirationDate, card.cardExpirationDate);
            strcpy(transData.cardHolderData.primaryAccountNumber, card.primaryAccountNumber);
            // Terminal Data
            transData.terminalData.transAmount= terminal.transAmount;
            transData.terminalData.maxTransAmount= terminal.maxTransAmount;
            strcpy(transData.terminalData.transactionDate, terminal.transactionDate);
            recieveTransactionData(&transData);
        }
    }
}