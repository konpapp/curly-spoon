#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Get dollar input
    float dollars;
    do
    {
        dollars = get_float("Change owed?: ");
    }
    while (dollars < 0);
    int cents = round(dollars * 100);

    //Initialize variable counting coins for change
    int minCoins = 0;

    //Change using minimum number of coins
    while (cents > 0)
    {
        //Use quarters first
        if (cents >= 25)
        {
            cents -= 25;
            minCoins += 1;
        }
        //Then dimes
        else if (cents >= 10)
        {
            cents -= 10;
            minCoins += 1;
        }
        //Then nickels
        else if (cents >= 5)
        {
            cents -= 5;
            minCoins += 1;
        }
        //Then pennies
        else if (cents >= 1)
        {
            cents -= 1;
            minCoins += 1;
        }
    }

    printf("%i\n", minCoins);
}
