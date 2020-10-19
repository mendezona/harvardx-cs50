#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)//iterate over rows then columns
    {
        for (int x = 0; x < width; x++)
        {
            //calculate average of RGB for greyscale
            float avg = (image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue) / 3.0;
            image[y][x].rgbtRed = (int) round(avg);
            image[y][x].rgbtGreen = (int) round(avg);
            image[y][x].rgbtBlue = (int) round(avg);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempPixel;
    for (int y = 0; y < height; y++)//iterate over rows and columns
    {
        for (int x = 0; x < width / 2; x++)//flip pixel values in row
        {
            tempPixel = image[y][width - x - 1];
            image[y][width - x - 1] = image[y][x];
            image[y][x] = tempPixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE previousRow[width];
    RGBTRIPLE currentRow[width];
    float newRed;
    float newGreen;
    float newBlue;

    for (int y = 0; y < height; y++)//iterate over picture rows
    {
        for (int x = 0; x < width; x++)//iterate over picture height
        {
            currentRow[x] = image[y][x];//copy current pixel to current row array for subsequent pixels to refer to

            if (y == 0)
            {
                if (x == 0)//if in top left corner
                {
                    newRed = (image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 4.0;
                    newGreen = (image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 4.0;
                    newBlue = (image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 4.0;
                }

                else if (x == width - 1)//if top row right corner
                {
                    newRed = (image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x - 1].rgbtRed) / 4.0;
                    newGreen = (image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x - 1].rgbtGreen) / 4.0;
                    newBlue = (image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x - 1].rgbtBlue) / 4.0;
                }

                else//if top row bot not corner
                {
                    newRed = (currentRow[x - 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0;
                    newGreen = (currentRow[x - 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen +
                                image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0;
                    newBlue = (currentRow[x - 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0;
                }
            }

            else if (y == height - 1)
            {
                if (x == 0)//if in bottom left corner
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed) / 4.0;
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen) / 4.0;
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue) / 4.0;
                }

                else if (x == width - 1)//if bottom left corner
                {
                    newRed = (image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + previousRow[x].rgbtRed + previousRow[x - 1].rgbtRed) / 4.0;
                    newGreen = (image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + previousRow[x].rgbtGreen + previousRow[x - 1].rgbtGreen) / 4.0;
                    newBlue = (image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + previousRow[x].rgbtBlue + previousRow[x - 1].rgbtBlue) / 4.0;
                }

                else//if bottom row but not corner
                {
                    newRed = (currentRow[x - 1].rgbtRed + previousRow[x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed +
                              previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed) / 6.0;
                    newGreen = (currentRow[x - 1].rgbtGreen + previousRow[x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen +
                                previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen) / 6.0;
                    newBlue = (currentRow[x - 1].rgbtBlue + previousRow[x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue +
                               previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue) / 6.0;
                }
            }

            else
            {
                if (x == 0)//if on left edge excluding corners
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0;
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y +
                                1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0;
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0;
                }

                else if (x == width - 1)//if on right edge excluding corners
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x - 1].rgbtRed + image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x - 1].rgbtRed) / 6.0;
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x - 1].rgbtGreen + image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + image[y
                                + 1][x].rgbtGreen + image[y + 1][x - 1].rgbtGreen) / 6.0;
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x - 1].rgbtBlue + image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x - 1].rgbtBlue) / 6.0;
                }

                else//if in middle of image
                {
                    newRed = (previousRow[x - 1].rgbtRed + previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + currentRow[x - 1].rgbtRed +
                              image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x +
                                      1].rgbtRed) / 9.0;
                    newGreen = (previousRow[x - 1].rgbtGreen + previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + currentRow[x - 1].rgbtGreen +
                                image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x +
                                        1].rgbtGreen) / 9.0;
                    newBlue = (previousRow[x - 1].rgbtBlue + previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + currentRow[x - 1].rgbtBlue +
                               image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x +
                                       1].rgbtBlue) / 9.0;

                }
            }

            image[y][x].rgbtRed = (int) round(newRed);
            image[y][x].rgbtGreen = (int) round(newGreen);
            image[y][x].rgbtBlue = (int) round(newBlue);

        }

        for (int i = 0; i < width; i++)//copy current row to previous row as record for next iteration to refer to
        {
            previousRow[i] = currentRow[i];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE previousRow[width];//record original values of previous row
    RGBTRIPLE currentRow[width];//record original values of current row

    RGBTRIPLE borderPixel;
    borderPixel.rgbtRed = 0;
    borderPixel.rgbtGreen = 0;
    borderPixel.rgbtBlue = 0;

    double gxRed;
    double gxGreen;
    double gxBlue;

    double gyRed;
    double gyBlue;
    double gyGreen;

    for (int y = 0; y < height; y++)//iterate over rows
    {
        for (int x = 0; x < width; x++)//iterate over columns
        {
            currentRow[x] = image[y][x];//record original value of current row

            if (y == 0)//top row
            {
                if (x == 0)//top left corner
                {
                    gxRed = image[y][x + 1].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gxGreen = + image[y][x + 1].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen;
                    gxBlue = image[y][x + 1].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue;

                    gyRed = image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gyGreen = image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen;
                    gyBlue = image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue;
                }

                else if (x == width - 1)//top right corner
                {
                    gxRed = currentRow[x - 1].rgbtRed * -2 + image[y + 1][x - 1].rgbtRed * -1;
                    gxGreen = currentRow[x - 1].rgbtGreen * -2 + image[y + 1][x - 1].rgbtGreen * -1;
                    gxBlue = currentRow[x - 1].rgbtBlue * -2 + image[y + 1][x - 1].rgbtBlue * -1;

                    gyRed = image[y + 1][x].rgbtRed * 2 + image[y + 1][x - 1].rgbtRed;
                    gyGreen = image[y + 1][x].rgbtGreen * 2 + image[y + 1][x - 1].rgbtGreen;
                    gyBlue = image[y + 1][x].rgbtBlue * 2 + image[y + 1][x - 1].rgbtBlue;
                }

                else//top edge but not corners
                {
                    gxRed = currentRow[x - 1].rgbtRed * -2 + image[y][x + 1].rgbtRed * 2 + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x +
                            1].rgbtRed;
                    gxGreen = currentRow[x - 1].rgbtGreen * -2 + image[y][x + 1].rgbtGreen * 2 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x +
                              1].rgbtGreen;
                    gxBlue = currentRow[x - 1].rgbtBlue * -2 + image[y][x + 1].rgbtBlue * 2 + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x +
                             1].rgbtBlue;

                    gyRed = image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gyGreen = image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen;
                    gyBlue = image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue;
                }
            }

            else if (y == height - 1)//bottom row
            {
                if (x == 0)//bottom left corner
                {
                    gxRed = previousRow[x + 1].rgbtRed + image[y][x + 1].rgbtRed * 2;
                    gxGreen = previousRow[x + 1].rgbtGreen + image[y][x + 1].rgbtGreen * 2;
                    gxBlue = previousRow[x + 1].rgbtBlue + image[y][x + 1].rgbtBlue * 2;

                    gyRed = previousRow[x].rgbtRed * -2 + previousRow[x + 1].rgbtRed * -1;
                    gyGreen = previousRow[x].rgbtGreen * -2 + previousRow[x + 1].rgbtGreen * -1;
                    gyBlue = previousRow[x].rgbtBlue * -2 + previousRow[x + 1].rgbtBlue * -1;
                }

                else if (x == width - 1)//bottom right corner
                {
                    gxRed = previousRow[x - 1].rgbtRed * -1 + currentRow[x - 1].rgbtRed * -2;
                    gxGreen = previousRow[x - 1].rgbtGreen * -1 + currentRow[x - 1].rgbtGreen * -2;
                    gxBlue = previousRow[x - 1].rgbtBlue * -1 + currentRow[x - 1].rgbtBlue * -2;

                    gyRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x].rgbtRed * -2;
                    gyGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x].rgbtGreen * -2;
                    gyBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x].rgbtBlue * -2;
                }

                else//bottom edge but not corners
                {
                    gxRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x + 1].rgbtRed + currentRow[x - 1].rgbtRed * -2 + image[y][x + 1].rgbtRed * 2;
                    gxGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x + 1].rgbtGreen + currentRow[x - 1].rgbtGreen * -2 + image[y][x +
                              1].rgbtGreen * 2;
                    gxBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x + 1].rgbtBlue + currentRow[x - 1].rgbtBlue * -2 + image[y][x + 1].rgbtBlue
                             * 2;

                    gyRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x].rgbtRed * -2 + previousRow[x + 1].rgbtRed * -1;
                    gyGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x].rgbtGreen * -2 + previousRow[x + 1].rgbtGreen * -1;
                    gyBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x].rgbtBlue * -2 + previousRow[x + 1].rgbtBlue * -1;
                }
            }

            else
            {
                if (x == 0)//left edge but not corners
                {
                    gxRed = previousRow[x + 1].rgbtRed + image[y][x + 1].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gxGreen = previousRow[x + 1].rgbtGreen + image[y][x + 1].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen;
                    gxBlue = previousRow[x + 1].rgbtBlue + image[y][x + 1].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue;

                    gyRed = previousRow[x].rgbtRed * -2 + previousRow[x + 1].rgbtRed * -1 + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gyGreen = previousRow[x].rgbtGreen * -2 + previousRow[x + 1].rgbtGreen * -1 + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x +
                              1].rgbtGreen;
                    gyBlue = previousRow[x].rgbtBlue * -2 + previousRow[x + 1].rgbtBlue * -1 + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x +
                             1].rgbtBlue;
                }

                else if (x == width - 1)//right edge but not corners
                {
                    gxRed = previousRow[x - 1].rgbtRed * -1 + currentRow[x - 1].rgbtRed * -2 + image[y + 1][x - 1].rgbtRed * -1;
                    gxGreen = previousRow[x - 1].rgbtGreen * -1 + currentRow[x - 1].rgbtGreen * -2 + image[y + 1][x - 1].rgbtGreen * -1;
                    gxBlue = previousRow[x - 1].rgbtBlue * -1 + currentRow[x - 1].rgbtBlue * -2 + image[y + 1][x - 1].rgbtBlue * -1;

                    gyRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x].rgbtRed * -2 + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed * 2;
                    gyGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x].rgbtGreen * -2 + image[y + 1][x - 1].rgbtGreen + image[y +
                              1][x].rgbtGreen * 2;
                    gyBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x].rgbtBlue * -2 + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue *
                             2;
                }

                else//everything in the middle
                {
                    gxRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x + 1].rgbtRed + currentRow[x - 1].rgbtRed * -2 + image[y][x + 1].rgbtRed * 2
                            + image[y + 1][x - 1].rgbtRed * -1 + image[y + 1][x + 1].rgbtRed;
                    gxGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x + 1].rgbtGreen + currentRow[x - 1].rgbtGreen * -2 + image[y][x +
                              1].rgbtGreen * 2 + image[y + 1][x - 1].rgbtGreen * -1 + image[y + 1][x + 1].rgbtGreen;
                    gxBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x + 1].rgbtBlue + currentRow[x - 1].rgbtBlue * -2 + image[y][x + 1].rgbtBlue
                             * 2 + image[y + 1][x - 1].rgbtBlue * -1 + image[y + 1][x + 1].rgbtBlue;

                    gyRed = previousRow[x - 1].rgbtRed * -1 + previousRow[x].rgbtRed * -2 + previousRow[x + 1].rgbtRed * -1 + image[y + 1][x -
                            1].rgbtRed + image[y + 1][x].rgbtRed * 2 + image[y + 1][x + 1].rgbtRed;
                    gyGreen = previousRow[x - 1].rgbtGreen * -1 + previousRow[x].rgbtGreen * -2 + previousRow[x + 1].rgbtGreen * -1 + image[y + 1][x -
                              1].rgbtGreen + image[y + 1][x].rgbtGreen * 2 + image[y + 1][x + 1].rgbtGreen;
                    gyBlue = previousRow[x - 1].rgbtBlue * -1 + previousRow[x].rgbtBlue * -2 + previousRow[x + 1].rgbtBlue * -1 + image[y + 1][x -
                             1].rgbtBlue + image[y + 1][x].rgbtBlue * 2 + image[y + 1][x + 1].rgbtBlue;
                }
            }

            //ensure that new pixel value does not exceed 255
            if (sqrt(pow(gxRed, 2) + pow(gyRed, 2)) > 255)
            {
                image[y][x].rgbtRed = 255;
            }

            else
            {
                image[y][x].rgbtRed = (int) round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            }

            if (sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)) > 255)
            {
                image[y][x].rgbtGreen = 255;
            }

            else
            {
                image[y][x].rgbtGreen = (int) round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            }

            if (sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)) > 255)
            {
                image[y][x].rgbtBlue = 255;
            }

            else
            {
                image[y][x].rgbtBlue = (int) round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            }

        }

        for (int i = 0; i < width; i++)//copy current row to previous row as record for next iteration to refer to
        {
            previousRow[i] = currentRow[i];
        }

    }
    return;

}
