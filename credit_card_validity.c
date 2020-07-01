#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //get number input
    long input;
    do
    {
        input = get_long("Number: ");
    }
    while (input <= 0);

    int digits = 0;

    long num = input;

    //check number of digits
    do
    {
        digits++;
        num /= 10;
    }
    while (num > 0);

    //printf("No. of digits: %i\n", digits);

    //check valid card according to Luhn's Algorithm
    int sum = 0;
    long digit;
    long power;
    //variables for checking card provider
    int firstEvenDigit;
    int firstOddDigit;

    for (int i = 2; i <= digits; i += 2)
    {
        power = pow(10, i);
        digit = input % (power) / pow(10, i - 1);
        //if multiplication by 2 results in double digit number, add those digits
        if (digit * 2 > 9)
        {
            sum += (digit * 2 / 10) + (digit * 2 % 10);
        }
        //else add multiplication by 2
        else
        {
            sum += digit * 2;
        }
        //store first digit from even number for checking card provider later
        firstEvenDigit = digit;
    }

    for (int i = 1; i <= digits; i += 2)
    {

        power = pow(10, i);
        digit = input % (power) / pow(10, i - 1);
        sum += digit;
        //store first digit from odd number for checking card provider later
        firstOddDigit = digit;
    }

    int lastDigit = sum % 10;

    //bool variable for validity
    bool legit = false;
    if (lastDigit == 0)
    {
        legit = true;
    }

    if (legit == true)
    {
        if (firstEvenDigit == 5 && (firstOddDigit >= 1 && firstOddDigit <= 5) && digits == 16)
        {
            printf("%s\n", "MASTERCARD");
        }
        else if (firstEvenDigit == 4 && (digits == 13 || digits == 16))
        {
            printf("%s\n", "VISA");
        }
        else if (firstOddDigit == 3 && (firstEvenDigit == 4 || firstEvenDigit == 7) && digits == 15)
        {
            printf("%s\n", "AMEX");
        }
        else
        {
            printf("%s\n", "INVALID");
        }
    }
    else
    {
        printf("%s\n", "INVALID");
    }

}
