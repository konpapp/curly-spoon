#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check for one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Ensure that the file can be opened.
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    FILE *img;
    //Assing dynamic memory for buffer to temporary store a block size from FAT file system (512 bytes)
    unsigned char *buffer = malloc(512 * sizeof(int));
    int count = 0;
    char filename[8];

    while (fread(buffer, 512, 1, file))
    {
        //JPEG format for the first 4 bytes is 0xff, 0xd8, 0xff, 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If it's not the first JPEG file, close the currently open file
            if (count > 0)
            {
                fclose(img);
            }

            //Create a string in the ###.jpg format, starting from 000.jpg
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            count++;
        }
        else if (count > 0)
        {
            fwrite(buffer, 512, 1, img);
        }

    }
    fclose(img);
    fclose(file);
    free(buffer);
}
