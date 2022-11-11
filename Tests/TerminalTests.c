#include <stdio.h>
#include <string.h>

#include "../Source/Terminal/terminal.c"

void getTransactionDateTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 1;
    ST_terminalData_t Test_Array;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: getTransactionDate");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", "Dummy Test (Time from Computer)");
        printf("%s", "Expected Result: ");
        printf("%s\n", " 24/10/2022 ");
        printf("%s", "Actual Result:    ");
        getTransactionDate(&Test_Array);
        printf("%s\n", Test_Array.transactionDate);
        printf("%s\n", " ");
    }
}

void isCardExpriedTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_cardData_t Test_Array1[Tests_Number];
    ST_terminalData_t Test_Array2[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    strcpy(Test_Array1[0].cardExpirationDate, "05/11");
    strcpy(Test_Array2[0].transactionDate, "11/12/2020");
    strcpy(Test_Array1[1].cardExpirationDate, "10/22");
    strcpy(Test_Array2[1].transactionDate, "1/10/2022");
    strcpy(Test_Array1[2].cardExpirationDate, "04/22");         // OK
    strcpy(Test_Array2[2].transactionDate, "05/03/2021");
    strcpy(Test_Array1[3].cardExpirationDate, "07/26");         // OK
    strcpy(Test_Array2[3].transactionDate, "12/07/2022");
    strcpy(Test_Array1[4].cardExpirationDate, "12/2021");       // OK
    strcpy(Test_Array2[4].transactionDate, "11/11/2021");
    strcpy(Test_Array1[5].cardExpirationDate, "05/19");
    strcpy(Test_Array2[5].transactionDate, "11/12/2020");
    
    // Expected Test Results
    Test_Result_Array[0]= 2;
    Test_Result_Array[1]= 2;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 0;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 2;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: isCardExpried");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s\n", "Input Data: ");
        printf("%s", "Card Expiration Date: ");
        printf("%s\n", Test_Array1[i].cardExpirationDate);
        printf("%s","Transcation Date:  ");
        printf("%s\n",Test_Array2[i].transactionDate);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", isCardExpired(&Test_Array1[i], &Test_Array2[i]) );
        printf("%s\n", " ");
    }
}

void getTransactionAmountTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_terminalData_t Test_Array[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    Test_Array[0].transAmount = -301.0;
    Test_Array[1].transAmount = 0.0;
    Test_Array[2].transAmount = 645.45;            // OK
    Test_Array[3].transAmount = 1.0;               // OK
    Test_Array[4].transAmount = 0.23;              // OK
    Test_Array[5].transAmount = -0.25;

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
        printf("%s\n", "Function Name: getTransactionAmount");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%f\n", Test_Array[i].transAmount);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", getTransactionAmount(&Test_Array[i]));
        printf("%s\n", " ");
    }
}

void isBelowMaxAmountTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_terminalData_t Test_Array[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    Test_Array[0].maxTransAmount = 789.0;           // OK
    Test_Array[0].transAmount = 465.0;
    Test_Array[1].maxTransAmount = 5550.0;
    Test_Array[1].transAmount = 78978.0;
    Test_Array[2].maxTransAmount = 46254;           // OK
    Test_Array[2].transAmount = 46.0;
    Test_Array[3].maxTransAmount = 12131.0;
    Test_Array[3].transAmount = 1000000.0;
    Test_Array[4].maxTransAmount = 1.0;             // OK
    Test_Array[4].transAmount = 0.25;   
    Test_Array[5].maxTransAmount = 10000.0;             //OK
    Test_Array[5].transAmount = 10000.0;

    // Expected Test Results
    Test_Result_Array[0]= 0;
    Test_Result_Array[1]= 5;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 5;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 0;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: isBelowMaxAmount");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s\n", "Input Data: ");
        printf("%s","Transfer Amount: ");
        printf("%f\n", Test_Array[i].transAmount);
        printf("%s","Max Transfer Amount: ");
        printf("%f\n", Test_Array[i].maxTransAmount);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", isBelowMaxAmount(&Test_Array[i]));
        printf("%s\n", " ");
    }
}

void setMaxAmountTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_terminalData_t Test_Array1[Tests_Number];
    float Test_Array2[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    Test_Array2[0] = -301.0;
    Test_Array2[1] = 0.0;
    Test_Array2[2] = 645.45;            // OK
    Test_Array2[3] = 1.0;               // OK
    Test_Array2[4] = 0.23;              // OK
    Test_Array2[5]= -0.25;

    // Expected Test Results
    Test_Result_Array[0]= 6;
    Test_Result_Array[1]= 6;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 0;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 6;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: setMaxAmount");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%f\n", Test_Array2[i]);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", setMaxAmount(&Test_Array1[i], Test_Array2[i]));
        printf("%s\n", " ");
    }
}

void main(void)
{
    getTransactionDateTest();
    printf("%s\n", "--------------------------------------------------- ");
    isCardExpriedTest();
    printf("%s\n", "--------------------------------------------------- ");
    getTransactionAmountTest();
    printf("%s\n", "--------------------------------------------------- ");
    isBelowMaxAmountTest();
    printf("%s\n", "--------------------------------------------------- ");
    setMaxAmountTest();
    printf("%s\n", "--------------------------------------------------- ");
}