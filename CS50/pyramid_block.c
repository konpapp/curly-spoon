#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get height
    int height;
    do
    {
        height  = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //printf("Stored: %i\n", height);

    for (int i = 0; i < height; i++)
    {
        //moving towards right
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        //building left pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("  ");

         //building right pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
