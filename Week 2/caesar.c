#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)//prompt user for correct input
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    else
    {
        for (int i = 0; i < strlen(argv[1]); i++) //iterate over string to make sure every character is a digit
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");//prompt for correct input if non digit detected
                return 1;
            }
        }

        int key = atoi(argv[1]);//convert string character to integer
        string plaintext = get_string("plaintext: ");//prompt user for plaintext to encrypt

        printf("ciphertext: ");
        for (int i = 0, textlength = strlen(plaintext); i < textlength; i++)//iterate over characters in plaintext
        {
            if (isalpha(plaintext[i]) != 0)//check if character is alphabetical
            {
                if (isupper(plaintext[i]) != 0)//if uppcase
                {
                    int cipherNum = ((int) plaintext[i] + key - (int) 'A') % 26;//perform cipher and look up ASCII key to print
                    printf("%c", (int) 'A' + cipherNum);
                }

                else if (islower(plaintext[i]) != 0)
                {
                    int cipherNum = ((int) plaintext[i] + key - (int) 'a') % 26;//perform cipher and look up ASCII key to print
                    printf("%c", (int) 'a' + cipherNum);
                }
            }

            else
            {
                printf("%c", plaintext[i]);//print same character if not alphabetical
            }
        }

        printf("\n");
        return 0;
    }
}