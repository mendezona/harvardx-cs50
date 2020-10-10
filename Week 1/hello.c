#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); // gets variable name using training wheels of CS50 library
    printf("hello, %s\n", name); // prints name given
}