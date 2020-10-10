#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float num; // initalise num
    do
    {
        num = get_float("Change owed: ");//get input
    }
    while (num < 0);//make sure input is not negative value

    int cents = round(num * 100); //convert to int
    int count = 0; //initalise count

    while (cents >= 25) //count multiples of 0.25
    {
        cents -= 25;
        count++;
    }

    while (cents >= 10) //count multiples of 0.1
    {
        cents -= 10;
        count++;
    }

    while (cents >= 5) //count multiples of 0.05
    {
        cents -= 5;
        count++;
    }

    while (cents >= 1) //count multiples of 0.01
    {
        cents -= 1;
        count++;
    }

    printf("%i\n", count);
}