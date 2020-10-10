#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int caseDifference = (int) 'a' - (int) 'A';

    if (argc != 2)//prompt user for correct input
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    else if (strlen(argv[1]) < ((int) 'z' - (int) 'a'))//prompt user for 26 key character input
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {
        for (int i = 0; i < strlen(argv[1]); i++) //iterate over string to make sure every character is a letter
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Key must only contain alphabetic characters\n");//prompt for correct input if non letter detected
                return 1;
            }
        }

        for (int i = 0; i < strlen(argv[1]); i++) //iterate over string to make sure every character is a letter
        {
            for (int x = i + 1; x < strlen(argv[1]); x++) //compare iteraiton above against all future key characters
            {

                if (argv[1][i] == argv[1][x])
                {
                    printf("Key must not contain repeated characters\n");//prompt for correct input if duplicate letter detected in samecase
                    return 1;
                }

                else if (isupper(argv[1][i]) != 0)
                {
                    if ((int) argv[1][x] - (int) argv[1][i] == caseDifference)//difference between uppercase and lowercase in ASCII
                    {
                        printf("Key must not contain repeated characters\n");//prompt for correct input if duplicate letter detected in lowercase
                        return 1;
                    }
                }

                else if (islower(argv[1][i]) != 0)
                {
                    if ((int) argv[1][i] - (int) argv[1][x] == caseDifference)//difference between uppercase and lowercase in ASCII
                    {
                        printf("Key must not contain repeated characters\n");//prompt for correct input if duplicate letter detected in uppercase
                        return 1;
                    }
                }
            }
        }

        string plaintext = get_string("plaintext: ");//prompt user for plaintext to encrypt
        printf("ciphertext: ");
        for (int i = 0, x = strlen(plaintext); i < x; i++)//iterate over plain text
        {
            if (isalpha(plaintext[i]) != 0)//check if plaintext character is alphabetical
            {
                // printf("plaintext test: %c\n", plaintext[i]);
                if (isupper(plaintext[i]) != 0)//if plaintext character is uppercase
                {
                    char cipherLetter = argv[1][(int) plaintext[i] - (int) 'A'];
                    if (islower(cipherLetter) != 0)//if cipher is uppcase but plaintext is lowercase
                    {
                        printf("%c", (int) cipherLetter - caseDifference);//get and print uppercase
                    }

                    else
                    {
                        printf("%c", cipherLetter);
                    }
                }

                if (islower(plaintext[i]) != 0)//if plaintext character is lowercase
                {
                    char cipherLetter = argv[1][(int) plaintext[i] - (int) 'a'];
                    if (isupper(cipherLetter) != 0)//if cipher is uppcase but plaintext is lowercase
                    {
                        printf("%c", (int) cipherLetter + caseDifference);//get and print lowercase
                    }

                    else
                    {
                        printf("%c", cipherLetter);
                    }
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