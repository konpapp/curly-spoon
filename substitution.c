#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowercase = "abcdefghijklmnopqrstuvwxyz";

bool validate_key_digits(string key);
int upper_key_index(char character);
int lower_key_index(char character);

int main(int argc, string argv[])
{
    //check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string keyString = argv[1];

    // method returning false when digits are not 26, or contain duplicates
    if (!validate_key_digits(keyString))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    char ciphertext[strlen(plaintext)];
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                //encrypt uppercase character according to key string
                ciphertext[i] = toupper(keyString[upper_key_index(plaintext[i])]);
            }
            else if (islower(plaintext[i]))
            {
                //encrypt lowercase character according to key string
                ciphertext[i] = tolower(keyString[lower_key_index(plaintext[i])]);
            }
        }
        //if not alphabetic character, assign directly
        else
        {
            ciphertext[i] = plaintext[i];
        }
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}

bool validate_key_digits(string key)
{
    //check for 26 digits
    int n = strlen(key);
    if (n != 26)
    {
        return false;
    }

    char count[n];
    for (int i = 0; i < n; i++)
    {
        //check for alphabetical characters
        if (!isalpha(key[i]))
        {
            return false;
        }

        //check for duplicates
        count[i] = tolower(key[i]);
        for (int j = 0; j < i; j++)
        {
            //if already registered characters match current character
            if (count[j] == count[i])
            {
                return false;
            }
        }
    }
    return true;
}

int upper_key_index(char character)
{
    int index = 0;
    //get associated index from uppercase alphabet
    while (character != uppercase[index])
    {
        index++;
    }
    return index;
}

int lower_key_index(char character)
{
    int index = 0;
    //get associated index from lowercase alphabet
    while (character != lowercase[index])
    {
        index++;
    }
    return index;
}
