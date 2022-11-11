#include <stdio.h>
#include <string.h>

#include "../Source/Server/server.c"

void recieveTransactionDataTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 4;
    ST_transaction_t Test_Array1[Tests_Number];
    ST_cardData_t Test_Array2[Tests_Number];
    ST_terminalData_t Test_Array3[Tests_Number];

    uint8_t Test_Result_Array[Tests_Number];
    
    // Test Cases
    // Test Case 1 : Approved
    // Card
    strcpy(Test_Array2[0].cardHolderName,"Islam Barakat");
    strcpy(Test_Array2[0].cardExpirationDate,"05/23");
    strcpy(Test_Array2[0].primaryAccountNumber,"123456789123456789");
    // Terminal
    Test_Array3[0].transAmount= 200.0;
    Test_Array3[0].maxTransAmount= 4000.0;
    strcpy(Test_Array3[0].transactionDate,"12/5/2022");
    // Transcation
    Test_Array1[0].cardHolderData = Test_Array2[0];
    Test_Array1[0].terminalData = Test_Array3[0];

    // Test Case 2 : Declined (Blocked)
    // Card
    strcpy(Test_Array2[1].cardHolderName,"Islam Barakat");
    strcpy(Test_Array2[1].cardExpirationDate,"05/23");
    strcpy(Test_Array2[1].primaryAccountNumber,"023184014521340335"); //<------ This is account is blocked in the Database
    // Terminal
    Test_Array3[1].transAmount= 200.0;
    Test_Array3[1].maxTransAmount= 4000.0;
    strcpy(Test_Array3[1].transactionDate,"12/5/2022");
    // Transcation
    Test_Array1[1].cardHolderData = Test_Array2[1];
    Test_Array1[1].terminalData = Test_Array3[1];

    // Test Case 3 : Declined (Low Balance)
    // Card
    strcpy(Test_Array2[2].cardHolderName,"Islam Barakat");
    strcpy(Test_Array2[2].cardExpirationDate,"05/23");
    strcpy(Test_Array2[2].primaryAccountNumber,"787987561076733238");  //<------ This is account exists and Running
    // Terminal
    Test_Array3[2].transAmount= 10000.0;                                //<------ Higher than Balance
    Test_Array3[2].maxTransAmount= 20000.0;
    strcpy(Test_Array3[2].transactionDate,"12/5/2022");
    // Transcation
    Test_Array1[2].cardHolderData = Test_Array2[2];
    Test_Array1[2].terminalData = Test_Array3[2];

    // Test Case 4 : Declined (Fraud)
    // Card
    strcpy(Test_Array2[3].cardHolderName,"Islam Barakat");
    strcpy(Test_Array2[3].cardExpirationDate,"05/23");
    strcpy(Test_Array2[3].primaryAccountNumber,"350878022047108742"); //<------ This is account Doesn't exist in the Database
    // Terminal
    Test_Array3[3].transAmount= 200.0;
    Test_Array3[3].maxTransAmount= 4000.0;
    strcpy(Test_Array3[3].transactionDate,"12/5/2022");
    // Transcation
    Test_Array1[3].cardHolderData = Test_Array2[3];
    Test_Array1[3].terminalData = Test_Array3[3];

    // Test Results
    Test_Result_Array[0]= 0;
    Test_Result_Array[1]= 2;
    Test_Result_Array[2]= 1;
    Test_Result_Array[3]= 3;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: recieveTransactionData");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s\n", "Input Data: ");
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", recieveTransactionData(&Test_Array1[i]));
        printf("%s\n", " ");
    }
}

void isValidAccountTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_cardData_t Test_Array1[Tests_Number];
    ST_accountsDB_t Test_Array2[Tests_Number];

    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    strcpy(Test_Array1[0].primaryAccountNumber, "123456789123456789");         // OK
    strcpy(Test_Array1[1].primaryAccountNumber, "456464132");
    strcpy(Test_Array1[2].primaryAccountNumber, "023184014521340335");        // OK
    strcpy(Test_Array1[3].primaryAccountNumber, "10235kdfjslgk14389");
    strcpy(Test_Array1[4].primaryAccountNumber, "kljdf8bifdjblkk");
    strcpy(Test_Array1[5].primaryAccountNumber, "3213");
    
    // Test Results
    Test_Result_Array[0]= 0;
    Test_Result_Array[1]= 3;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 3;
    Test_Result_Array[4]= 3;
    Test_Result_Array[5]= 3;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: isValidAccount");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", Test_Array1[i].primaryAccountNumber);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", isValidAccount(&Test_Array1[i], &Test_Array2[i]));
        printf("%s\n", " ");
    }
}

void isBlockedAccountTest(void)
{
        // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_accountsDB_t Test_Array[Tests_Number];
    EN_accountState_t S_RUNNING = RUNNING;
    EN_accountState_t S_BLOCKED = BLOCKED;

    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    Test_Array[0].state = S_RUNNING;        // OK
    Test_Array[1].state = S_BLOCKED;
    Test_Array[2].state = S_BLOCKED;        
    Test_Array[3].state = S_RUNNING;        // OK
    Test_Array[4].state = S_RUNNING;        // OK
    Test_Array[5].state = S_BLOCKED;
    
    // Test Results
    Test_Result_Array[0]= 0;
    Test_Result_Array[1]= 5;
    Test_Result_Array[2]= 5;
    Test_Result_Array[3]= 0;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 5;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: isBlockedAccount");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%d\n", Test_Array[i].state);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", isBlockedAccount(&Test_Array[i]));
        printf("%s\n", " ");
    }
}
void isAmountAvailableTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_terminalData_t Test_Array1[Tests_Number];
    ST_accountsDB_t Test_Array2[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    Test_Array1[0].transAmount = 78978.0;        
    Test_Array2[0].balance = 33516.0;
    Test_Array1[1].transAmount = 45641.0;
    Test_Array2[1].balance = 13240.0;
    Test_Array1[2].transAmount = 10000.0;         // OK
    Test_Array2[2].balance = 20000000.0;
    Test_Array1[3].transAmount = 3000.0;          // OK         
    Test_Array2[3].balance = 6000.0;
    Test_Array1[4].transAmount = 56523.0;         // OK
    Test_Array2[4].balance = 56523.0;
    Test_Array1[5].transAmount = 500.0;
    Test_Array2[5].balance = 100.0;
    
    // Expected Test Results
    Test_Result_Array[0]= 4;
    Test_Result_Array[1]= 4;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 0;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 4;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: isAmountAvailable");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s\n", "Input Data: ");
        printf("%s", "Transcation Amount: ");
        printf("%f\n", Test_Array1[i].transAmount);
        printf("%s","Account Balance:  ");
        printf("%f\n",Test_Array2[i].balance);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", isAmountAvailable(&Test_Array1[i], &Test_Array2[i]) );
        printf("%s\n", " ");
    }
}
void saveTransactionTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 1;
    ST_transaction_t Test_Array;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: getTransactionDate");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", "Dummy Test (Return Always 0)");
        printf("%s", "Expected Result: ");
        printf("%d\n", 0);
        printf("%s", "Actual Result:    ");
        printf("%d\n", saveTransaction(&Test_Array));
        printf("%s\n", " ");
    }
}
void listSavedTransactionsTest(void);

void main(void)
{
    fillAccountsDataBase();
    recieveTransactionDataTest();
    printf("%s\n", "--------------------------------------------------- ");
    isValidAccountTest();
    printf("%s\n", "--------------------------------------------------- ");
    isBlockedAccountTest();
    printf("%s\n", "--------------------------------------------------- ");
    isAmountAvailableTest();
    printf("%s\n", "--------------------------------------------------- ");
    // saveTransactionTest();
    // printf("%s\n", "--------------------------------------------------- ");
}