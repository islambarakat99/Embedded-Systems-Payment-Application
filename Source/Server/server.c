
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

ST_accountsDB_t accountsDB[255];
ST_transaction_t transactions[255];
uint8_t lastTranscationIndex = 0;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    ST_accountsDB_t accountRef;

    if (isValidAccount(&transData->cardHolderData, &accountRef) == SERVER_OK)
    {
        if (isBlockedAccount(&accountRef) == BLOCKED_ACCOUNT)
        {
            transData->transState = DECLINED_STOLEN_CARD;
            return DECLINED_STOLEN_CARD;
        }
        else if (isAmountAvailable(&transData->terminalData, &accountRef) == LOW_BALANCE)
        {
            transData->transState = DECLINED_INSUFFECIENT_FUND;
            return DECLINED_INSUFFECIENT_FUND;
        }
        else if (saveTransaction(transData) == SAVING_FAILED)
        {
            transData->transState = INTERNAL_SERVER_ERROR;
            return INTERNAL_SERVER_ERROR;
        }
        else
        {
            accountRef.balance -= transData->terminalData.transAmount;
            transData->transState = APPROVED;
            return APPROVED;
        }
    }
    else
    {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    for(int i=0;i<255;i++)
    {   
        if (strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
        {
            *accountRefrence = accountsDB[i];
            return SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence->state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    }
    else
    {
        return SERVER_OK;   
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence->balance >= termData->transAmount )
    {
        return SERVER_OK;
    }
    else
    {
        return LOW_BALANCE;   
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static int SequenceNumber = 1;
   
    // Card Data
    strcpy(transactions[lastTranscationIndex].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
    strcpy(transactions[lastTranscationIndex].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
    strcpy(transactions[lastTranscationIndex].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
    // Terminal Data
    transactions[lastTranscationIndex].terminalData.transAmount= transData->terminalData.transAmount;
    transactions[lastTranscationIndex].terminalData.maxTransAmount= transData->terminalData.maxTransAmount;
    strcpy(transactions[lastTranscationIndex].terminalData.transactionDate, transData->terminalData.transactionDate);
    // State
    transactions[lastTranscationIndex].transState = transData->transState;
    // Sequence Number
    transactions[lastTranscationIndex].transactionSequenceNumber = SequenceNumber;
    SequenceNumber++;

    lastTranscationIndex++;

    listSavedTransactions();

    return SERVER_OK;
}

void listSavedTransactions(void)
{
    for (int i=0;i<lastTranscationIndex;i++)
    {
        printf("%s\n"," ");
        printf("%s\n","#########################");
        printf("%s","Transaction Sequence Number: ");
        printf("%d\n", transactions[i].transactionSequenceNumber);
        printf("%s","Transaction Date: ");
        printf("%s\n", transactions[i].terminalData.transactionDate);
        printf("%s","Transaction Amount: ");
        printf("%f\n", transactions[i].terminalData.transAmount);
        printf("%s","Transaction State: ");
        printf("%d\n", transactions[i].transState);
        printf("%s","Terminal Max Amount: ");
        printf("%f\n", transactions[i].terminalData.maxTransAmount);
        printf("%s","Cardholder Name: ");
        printf("%s\n", transactions[i].cardHolderData.cardHolderName);
        printf("%s","PAN: ");
        printf("%s\n", transactions[i].cardHolderData.primaryAccountNumber);
        printf("%s","Card Expiration Date: ");
        printf("%s\n", transactions[i].cardHolderData.cardExpirationDate);
        printf("%s\n","#########################");
    }
}

void fillAccountsDataBase(void)
{
    // Account 1
    accountsDB[0].balance = 5000.0;
    accountsDB[0].state = RUNNING;
    strcpy(accountsDB[0].primaryAccountNumber ,"123456789123456789");
    // Account 2
    accountsDB[1].balance = 1000000.0;
    accountsDB[1].state = RUNNING;
    strcpy(accountsDB[1].primaryAccountNumber ,"123456789124567890");
    // Account 3
    accountsDB[2].balance = 89000.0;
    accountsDB[2].state = BLOCKED;
    strcpy(accountsDB[2].primaryAccountNumber ,"123456789178743540");
    // Account 4
    accountsDB[3].balance = 5000.0;
    accountsDB[3].state = BLOCKED;
    strcpy(accountsDB[3].primaryAccountNumber ,"023184014521340335");
    // Account 5
    accountsDB[4].balance = 5000.0;
    accountsDB[4].state = RUNNING;
    strcpy(accountsDB[4].primaryAccountNumber ,"787987561076733238");

    // Fill 10 more Accounts Randomly
    for (int i=5; i < 15; i++)
    {
        accountsDB[i].balance =  rand();
        if (i%2==0)
        {
            accountsDB[i].state = RUNNING;
        }
        else
        {            
            accountsDB[i].state = BLOCKED;
        }
        for (int j=0;j<19;j++)
        {   
            int temp = rand()%10;
            accountsDB[i].primaryAccountNumber[j] = temp;
        }
    }
}
