#include <stdio.h>
#include <string.h>

#include "../Source/Card/card.c"

void getCardHolderNameTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_cardData_t Test_Array[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    strcpy(Test_Array[0].cardHolderName, "Islam Barakat");
    strcpy(Test_Array[1].cardHolderName, "456464132");
    strcpy(Test_Array[2].cardHolderName, "Islam Mohamed Barakat");          // OK
    strcpy(Test_Array[3].cardHolderName, "UOIDUFIGOUPOIFUOPO");
    strcpy(Test_Array[4].cardHolderName, "kljdf8bifdjblkk");
    strcpy(Test_Array[5].cardHolderName, "Islam Barakat");
    
    // Expected Test Results
    Test_Result_Array[0]= 1;
    Test_Result_Array[1]= 1;
    Test_Result_Array[2]= 0;
    Test_Result_Array[3]= 1;
    Test_Result_Array[4]= 1;
    Test_Result_Array[5]= 1;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: getCardHolderName");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", Test_Array[i].cardHolderName);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", getCardHolderName(&Test_Array[i]));
        printf("%s\n", " ");
    }
}

void getCardExpiryDateTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_cardData_t Test_Array[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    strcpy(Test_Array[0].cardExpirationDate, "05/12");          // OK
    strcpy(Test_Array[1].cardExpirationDate, "32/78");
    strcpy(Test_Array[2].cardExpirationDate, "45546");
    strcpy(Test_Array[3].cardExpirationDate, "45");
    strcpy(Test_Array[4].cardExpirationDate, "465456");
    strcpy(Test_Array[5].cardExpirationDate, "05/142");
    
    // Expected Test Results
    Test_Result_Array[0]= 0;
    Test_Result_Array[1]= 2;
    Test_Result_Array[2]= 2;
    Test_Result_Array[3]= 2;
    Test_Result_Array[4]= 2;
    Test_Result_Array[5]= 2;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: getCardExpiryDateTest");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", Test_Array[i].cardExpirationDate);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", getCardExpiryDate(&Test_Array[i]));
        printf("%s\n", " ");
    }
}

void getCardPANTest(void)
{
    // Number of Test Cases
    uint8_t Tests_Number = 6;
    ST_cardData_t Test_Array[Tests_Number];
    uint8_t Test_Result_Array[Tests_Number];

    // Test Cases
    strcpy(Test_Array[0].primaryAccountNumber, "9789897/9797");
    strcpy(Test_Array[1].primaryAccountNumber, "0450");
    strcpy(Test_Array[2].primaryAccountNumber, "jghjghjghjhgjfgjhfg");
    strcpy(Test_Array[3].primaryAccountNumber, "788476573475547473657");
    strcpy(Test_Array[4].primaryAccountNumber, "54315541534151435");                // OK
    strcpy(Test_Array[5].primaryAccountNumber, "546 526 52 6 326. 41");
    
    // Expected Test Results
    Test_Result_Array[0]= 3;
    Test_Result_Array[1]= 3;
    Test_Result_Array[2]= 3;
    Test_Result_Array[3]= 3;
    Test_Result_Array[4]= 0;
    Test_Result_Array[5]= 3;

    for (int i=0;i<Tests_Number;i++)
    {
        printf("%s\n", "Tester Name: Islam Barakat");
        printf("%s\n", "Function Name: getCardPANTest");
        printf("%s", "Test Case ");
        printf("%d", i+1);
        printf("%s\n", ":");
        printf("%s", "Input Data: ");
        printf("%s\n", Test_Array[i].primaryAccountNumber);
        printf("%s", "Expected Result: ");
        printf("%d\n", Test_Result_Array[i]);
        printf("%s", "Actual Result:   ");
        printf("%d\n", getCardPAN(&Test_Array[i]));
        printf("%s\n", " ");
    }
}

void main(void)
{
    getCardHolderNameTest();
    printf("%s\n", "--------------------------------------------------- ");
    getCardExpiryDateTest();
    printf("%s\n", "--------------------------------------------------- ");
    getCardPANTest();
}