#include "helpers.h"
#include <math.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)//iterate over rows then columns
    {
        for (int x = 0, sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0; x < width; x++)
        {
            //calculate sepia values for RGB values
            sepiaRed = round(0.393 * image[y][x].rgbtRed + 0.769 * image[y][x].rgbtGreen + 0.189 * image[y][x].rgbtBlue);
            sepiaGreen = round(0.349 * image[y][x].rgbtRed + 0.686 * image[y][x].rgbtGreen + 0.168 * image[y][x].rgbtBlue);
            sepiaBlue = round(0.272 * image[y][x].rgbtRed + 0.534 * image[y][x].rgbtGreen + 0.131 * image[y][x].rgbtBlue);

            //ensure sepia value is maximum 255 to fit in 8 bit image
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

            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue;
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
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 4.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 4.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else if (x == width - 1)//if top row but not corner
                {
                    newRed = (image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x - 1].rgbtRed) / 4.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x - 1].rgbtGreen) / 4.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x - 1].rgbtBlue) / 4.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else//if in top right corner
                {
                    newRed = (currentRow[x - 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (currentRow[x - 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen +
                                image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (currentRow[x - 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }
            }

            else if (y == height - 1)
            {
                if (x == 0)//if in bottom left corner
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed) / 4.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen) / 4.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue) / 4.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else if (x == width - 1)//if in bottom row but not corner
                {
                    newRed = (image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + previousRow[x].rgbtRed + previousRow[x - 1].rgbtRed) / 4.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + previousRow[x].rgbtGreen + previousRow[x - 1].rgbtGreen) / 4.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + previousRow[x].rgbtBlue + previousRow[x - 1].rgbtBlue) / 4.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else//if in bottom right corner
                {
                    newRed = (currentRow[x - 1].rgbtRed + previousRow[x - 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed +
                              previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed) / 6.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (currentRow[x - 1].rgbtGreen + previousRow[x - 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen +
                                previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen) / 6.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (currentRow[x - 1].rgbtBlue + previousRow[x - 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue +
                               previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue) / 6.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }
            }

            else
            {
                if (x == 0)//if on left edge excluding corners
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 6.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y +
                                1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 6.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 6.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else if (x == width - 1)//if on right edge excluding corners
                {
                    newRed = (previousRow[x].rgbtRed + previousRow[x - 1].rgbtRed + image[y][x].rgbtRed + currentRow[x - 1].rgbtRed + image[y +
                              1][x].rgbtRed + image[y + 1][x - 1].rgbtRed) / 6.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (previousRow[x].rgbtGreen + previousRow[x - 1].rgbtGreen + image[y][x].rgbtGreen + currentRow[x - 1].rgbtGreen + image[y
                                + 1][x].rgbtGreen + image[y + 1][x - 1].rgbtGreen) / 6.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (previousRow[x].rgbtBlue + previousRow[x - 1].rgbtBlue + image[y][x].rgbtBlue + currentRow[x - 1].rgbtBlue + image[y +
                               1][x].rgbtBlue + image[y + 1][x - 1].rgbtBlue) / 6.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }

                else//if in middle of image
                {
                    newRed = (previousRow[x - 1].rgbtRed + previousRow[x].rgbtRed + previousRow[x + 1].rgbtRed + currentRow[x - 1].rgbtRed +
                              image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x +
                                      1].rgbtRed) / 9.0;
                    image[y][x].rgbtRed = (int) round(newRed);
                    newGreen = (previousRow[x - 1].rgbtGreen + previousRow[x].rgbtGreen + previousRow[x + 1].rgbtGreen + currentRow[x - 1].rgbtGreen +
                                image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x +
                                        1].rgbtGreen) / 9.0;
                    image[y][x].rgbtGreen = (int) round(newGreen);
                    newBlue = (previousRow[x - 1].rgbtBlue + previousRow[x].rgbtBlue + previousRow[x + 1].rgbtBlue + currentRow[x - 1].rgbtBlue +
                               image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x +
                                       1].rgbtBlue) / 9.0;
                    image[y][x].rgbtBlue = (int) round(newBlue);
                }
            }

        }

        for (int i = 0; i < width; i++)//copy current row to previous row as record for next iteration to refer to
        {
            previousRow[i] = currentRow[i];
        }
    }
    return;
}
