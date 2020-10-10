#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long cardNum;
    do
    {
        cardNum = get_long("Number: ");//gets card number from user
    }
    while (cardNum < 0); //ensure number is greater than one

    //gets each number of the card without a list
    int oneNum = (cardNum % 10 - cardNum % 1);
    int twoNum = (cardNum % 100 - cardNum % 10) / 10;
    int threeNum = (cardNum % 1000 - cardNum % 100) / 100;
    int fourNum = (cardNum % 10000 - cardNum % 1000) / 1000;
    int fiveNum = (cardNum % 100000 - cardNum % 10000) / 10000;
    int sixNum = (cardNum % 1000000 - cardNum % 100000) / 100000;
    int sevenNum = (cardNum % 10000000 - cardNum % 1000000) / 1000000;
    int eightNum = (cardNum % 100000000 - cardNum % 10000000) / 10000000;
    int nineNum = (cardNum % 1000000000 - cardNum % 100000000) / 100000000;
    int tenNum = (cardNum % 10000000000 - cardNum % 1000000000) / 1000000000;
    int elevenNum = (cardNum % 100000000000 - cardNum % 10000000000) / 10000000000;
    int twelveNum = (cardNum % 1000000000000 - cardNum % 100000000000) / 100000000000;
    int thirteenNum = (cardNum % 10000000000000 - cardNum % 1000000000000) / 1000000000000;
    int fourteenNum = (cardNum % 100000000000000 - cardNum % 10000000000000) / 10000000000000;
    int fifteenNum = (cardNum % 1000000000000000 - cardNum % 100000000000000) / 100000000000000;
    int sixteenNum = (cardNum % 10000000000000000 - cardNum % 1000000000000000) / 1000000000000000;

    //step 1 of performing checksum, t naming convention
    int tsixteenNum = sixteenNum * 2;
    int tfourteenNum = fourteenNum * 2;
    int ttwelveNum = twelveNum * 2;
    int ttenNum = tenNum * 2;
    int teightNum = eightNum * 2;
    int tsixNum = sixNum * 2;
    int tfourNum = fourNum * 2;
    int ttwoNum = twoNum * 2;

    //step 2 of performing checksum a/b naming
    int asixteenNum = (tsixteenNum % 10 - tsixteenNum % 1);
    int bsixteenNum = (tsixteenNum % 100 - tsixteenNum % 10) / 10;
    int atfourteenNum = (tfourteenNum % 10 - tfourteenNum % 1);
    int btfourteenNum = (tfourteenNum % 100 - tfourteenNum % 10) / 10;
    int attwelveNum = (ttwelveNum % 10 - ttwelveNum % 1);
    int bttwelveNum = (ttwelveNum % 100 - ttwelveNum % 10) / 10;
    int attenNum = (ttenNum % 10 - ttenNum % 1);
    int bttenNum = (ttenNum % 100 - ttenNum % 10) / 10;
    int ateightNum = (teightNum % 10 - teightNum % 1);
    int bteightNum = (teightNum % 100 - teightNum % 10) / 10;
    int atsixNum = (tsixNum % 10 - tsixNum % 1);
    int btsixNum = (tsixNum % 100 - tsixNum % 10) / 10;
    int atfourNum = (tfourNum % 10 - tfourNum % 1);
    int btfourNum = (tfourNum % 100 - tfourNum % 10) / 10;
    int attwoNum = (ttwoNum % 10 - ttwoNum % 1);
    int bttwoNum = (ttwoNum % 100 - ttwoNum % 10) / 10;

    //step 3 of performing checksum
    int evenSum = asixteenNum + bsixteenNum + atfourteenNum + btfourteenNum + attwelveNum + bttwelveNum + attenNum + bttenNum +
                  ateightNum + bteightNum + atsixNum + btsixNum + atfourNum + btfourNum + attwoNum + bttwoNum;

    //step 4 of performing checksum
    int finalChecksum = evenSum + oneNum + threeNum + fiveNum + sevenNum + nineNum + elevenNum + thirteenNum + fifteenNum;

    if (finalChecksum % 10 == 0)//valid checksum common across all cards
    {
        if (fifteenNum == 3)//begin check for AMEX
        {
            if (fourteenNum == 4 || fourteenNum == 7)
            {
                printf("AMEX\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        else if (sixteenNum == 5) //check for MasterCard
        {
            if (fifteenNum == 1 || fifteenNum == 2 || fifteenNum == 3 || fifteenNum == 4 || fifteenNum == 5)
            {
                printf("MASTERCARD\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        else if (sixteenNum == 4 || thirteenNum == 4)//check for VISA
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}