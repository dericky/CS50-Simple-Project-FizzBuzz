#include <stdio.h>
#include <cs50.h>


//This is a script to convert minutes in the shower to bottles of water used. 

int main(void)
{
    printf("Minutes: ");

    int minutes = get_int();
    printf("Bottles: %i\n", minutes * 12);
}

