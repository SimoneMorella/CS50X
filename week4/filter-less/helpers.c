#include "helpers.h"
#include <math.h>
#include <stdio.h>

int min(int a, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int mean = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mean = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    int originalRed, originalGreen, originalBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalBlue = image[i][j].rgbtBlue;
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            image[i][j].rgbtBlue = min(255, round(sepiaBlue));
            image[i][j].rgbtRed = min(255, round(sepiaRed));
            image[i][j].rgbtGreen = min(255, round(sepiaGreen));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp = image[0][0];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image [i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }

    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int length = 3;
    RGBTRIPLE copy[height][width];
    int array[3] = {-1, 0, 1};
    int sumRed = 0, sumGreen = 0, sumBlue = 0, counter = 0;
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copy[a][b] = image [a][b];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRed = sumGreen = sumBlue = counter = 0;
            if (i == 0)
            {
                if (j == 0)
                {
                    for (int x = 1; x < length; x++)
                    {
                        for (int y = 1; y < length; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }

                }
                if (j == width - 1)
                {
                    for (int x = 1; x < length; x++)
                    {
                        for (int y = 0; y < length - 1; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }
                }
                else
                {
                    for (int x = 1; x < length; x++)
                    {
                        for (int y = 0; y < length; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }
            if (i == height - 1)
            {
                if (j == 0)
                {
                    for (int x = 0; x < length - 1; x++)
                    {
                        for (int y = 1; y < length; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }
                }
                if (j == width - 1)
                {
                    for (int x = 0; x < length - 1; x++)
                    {
                        for (int y = 0; y < length - 1; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }
                }
                else
                {
                    for (int x = 0; x < length - 1; x++)
                    {
                        for (int y = 0; y < length; y++)
                        {
                            sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                            sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                            sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }
            if (j == 0)
            {
                for (int x = 0; x < length; x++)
                {
                    for (int y = 1; y < length; y++)
                    {
                        sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                        sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                        sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                        counter++;
                    }
                }
            }
            if (j == width - 1)
            {
                for (int x = 0; x < length; x++)
                {
                    for (int y = 0; y < length - 1; y++)
                    {
                        sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                        sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                        sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                        counter++;
                    }
                }
            }
            else
            {
                for (int x = 0; x < length; x++)
                {
                    for (int y = 0; y < length; y++)
                    {
                        sumRed += copy[i + array[x]][j + array[y]].rgbtRed;
                        sumGreen += copy[i + array[x]][j + array[y]].rgbtGreen;
                        sumBlue += copy[i + array[x]][j + array[y]].rgbtBlue;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / (counter * 1.0));
            image[i][j].rgbtGreen = round(sumGreen / (counter * 1.0));
            image[i][j].rgbtBlue = round(sumBlue / (counter * 1.0));
        }
    }
}

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}