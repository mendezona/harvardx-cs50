#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");//get text from user

    float letterCount = 0;//initalised to 0 to count letters in text
    float wordCount = 1;//initalised to get last word at end
    float sentanceCount = 0;

    for (int count = 0, n = strlen(text); count < n; count++)
    {
        if (text[count] >= 'A' && text[count] <= 'Z')//counts uppercase letters in text
        {
            letterCount++;
        }

        else if (text[count] >= 'a' && text[count] <= 'z')//counts lowercase letters in text
        {
            letterCount++;
        }

        else if (text[count] == ' ')//counts number of words
        {
            wordCount++;
        }

        else if (text[count] == '.' || text[count] == '!' || text[count] == '?')//counts number of sentances
        {
            sentanceCount++;
        }
    }

    float index = 0.0588 * (letterCount / wordCount * 100) - 0.296 * (sentanceCount / wordCount * 100)
                  - 15.8; //perform Coleman-Liau index formulat to calculate reading level

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}