#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height; //initialise input of height
    do
    {
        height = get_int("Height: ");//get user input
    }
    while (height < 1 || height > 8); //sets parameters above 0 and below 9

    for (int i = 0; i < height; i++) //vertical iteration
    {
        for (int j = 0; j < height; j++) //horizontal iteration
        {
            if (j < height - 1 - i) //print according to row
            {
                printf(" ");
            }

            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}