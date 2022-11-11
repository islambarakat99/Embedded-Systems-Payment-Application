
#include "terminal.h"
#include <stdio.h> 
#include <time.h>        
#include <string.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    // Store Current Date
    char current_Date[11];
    time_t t = time(NULL);
    struct tm *curr = localtime(&t);
    // Format
    strftime(current_Date, 11, "%d/%m/%Y", curr);
    // Store Value
    strcpy(termData->transactionDate, current_Date);
    
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    // Card Date
    int mm_card, yy_card;
    sscanf(cardData->cardExpirationDate,"%d/%d", &mm_card, &yy_card);

    // Terminal Date
    int dd, mm, yyyy;
    sscanf(termData->transactionDate,"%d/%d/%d", &dd, &mm , &yyyy);
    
    // Check Expiration
    if( yyyy < (2000+yy_card))
    {
        return TERMINAL_OK;
    }
    else if(yyyy == (2000+yy_card))
    {
        if(mm < mm_card)
            return TERMINAL_OK;
    }

    return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount <= 0.0) 
        return INVALID_AMOUNT;

    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->maxTransAmount < termData->transAmount)
        return EXCEED_MAX_AMOUNT;

    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    if (maxAmount <= 0.0) 
        return INVALID_MAX_AMOUNT;

    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    
}