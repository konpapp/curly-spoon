#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    //printf("%s\n", text);
    //printf("%i letter(s)\n", count_letters(text));
    //printf("%i word(s)\n", count_words(text));
    //printf("%i sentence(s)\n", count_sentences(text));

    //Coleman-Liau readability index = 0.0588 * L - 0.296 * S - 15.8
    float L = count_letters(text) / (float) count_words(text) * 100;
    float S = count_sentences(text) / (float) count_words(text) * 100;

    //printf("L: %f , S: %f\n", L, S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int letters = 0;
    //cheking if character in the range of A - z
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    //counting words only by checking for space between
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]) && (text[i - 1] == '.' || text[i - 1] == '?' || text[i - 1] == '!'))
        {
            sentences++;
        }
    }
    return sentences + 1;
}
