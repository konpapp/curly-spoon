#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const int alphabetDigits = 26;

int main(int argc, string argv[])
{
    //check for integer key
    if (argc != 2 || atoi(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //check if all digits integers
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //rotation number
    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);

    char ciphertext[n];
    printf("ciphertext: ");

    //minimize key value inside alphabetical range
    while (key > alphabetDigits)
    {
        key = key % alphabetDigits;
    }

    int buffer;
    for (int i = 0 ; i < n; i++)
    {
        buffer = plaintext[i] + key;
        //if character is lowercase, wrap a-z
        if (islower(plaintext[i]))
        {
            while (buffer > 'z')
            {
                buffer -= alphabetDigits;
            }
            ciphertext[i] = buffer;
        }
        //if character is uppercase, wrap A-Z
        else if (isupper(plaintext[i]))
        {
            while (buffer > 'Z')
            {
                buffer -= alphabetDigits;
            }
            ciphertext[i] = buffer;
        }
        //else just assign character
        else
        {
            ciphertext[i] = plaintext[i];
        }

        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}
