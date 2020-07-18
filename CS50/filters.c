#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Each pixel has the same Red, Green, Blue value, according to the average of the original
    //Float value for average to maintain accuracy
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.000);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Sepia algorithm
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            //Values must cap at 255 (8-bit color value)
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //Replacing rounded values into the original
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Temporary 2D matrix to save the reflected image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][width - j - 1];
        }
    }
    //Replacing into the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float averageRed;
    float averageGreen;
    float averageBlue;
    //Count variable for each pixel, measuring how many surrounding pixels are counted to calculate average
    int count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;
            count = 0;
            //Pixels not on the edges
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                //Helper loops in the surrounding pixels to extract average for each RGB value
                for (int z = i - 1; z <= i + 1; z++)
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Upper left corner
            else if (i == 0 && j == 0)
            {
                for (int z = i; z <= i + 1; z++)
                {
                    for (int k = j; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Upper right corner
            else if (i == 0 && j == width - 1)
            {
                for (int z = i; z <= i + 1; z++)
                {
                    for (int k = j - 1; k <= j; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Lower left corner
            else if (i == height - 1 && j == 0)
            {
                for (int z = i - 1; z <= i; z++)
                {
                    for (int k = j; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Lower right corner
            else if (i == height - 1 && j == width - 1)
            {
                for (int z = i - 1; z <= i; z++)
                {
                    for (int k = j - 1; k <= j; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //First row
            else if (i == 0)
            {
                for (int z = i; z <= i + 1; z++)
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //First column
            else if (j == 0)
            {
                for (int z = i - 1; z <= i + 1; z++)
                {
                    for (int k = j; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Last row
            else if (i == height - 1)
            {
                for (int z = i - 1; z <= i; z++)
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Last column
            else if (j == width - 1)
            {
                for (int z = i - 1; z <= i + 1; z++)
                {
                    for (int k = j - 1; k <= j; k++)
                    {
                        averageRed += image[z][k].rgbtRed;
                        averageBlue += image[z][k].rgbtBlue;
                        averageGreen += image[z][k].rgbtGreen;
                        count++;
                    }
                }
            }
            //Blurred values into the temporary matrix
            temp[i][j].rgbtRed = round(averageRed / count);
            temp[i][j].rgbtBlue = round(averageBlue / count);
            temp[i][j].rgbtGreen = round(averageGreen / count);
        }
    }
    //Replacing into the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
