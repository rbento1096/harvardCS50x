#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // sum all color channels and average them
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // assign each channel the avg value, obtaining a grayscale tone.
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // we only need to go to the middle of the image to reverse it
        // floor ensures it stops at the middle. If width is odd one line will be skipped, but that is the middle one, so it is already in position
        for (int j = 0; j < floor(width / 2); j++)
        {
            // stores a temp pixel with the current values
            RGBTRIPLE temp = image[i][j];
            // switches current value for the value on the opposite side. height and widt - 1 because of zero indexing.
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // makes a copy of the image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // all values are initialized as 0.
            float pixel_nr = 0;
            int red = 0;
            int blue = 0;
            int green = 0;

            // starting at -1, we will do 3 iterations
            for (int x = -1; x < 2; x++)
            {
                for (int y = - 1; y < 2; y++)
                {
                    // if pixel would be out of bounds, skip it
                    if (i + x < 0 || i + x > height - 1 ||  j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    // else increment the number of total pixels.
                    pixel_nr++;
                    // and sum the values for all current channels to the total
                    red += temp[i + x][j + y].rgbtRed;
                    green += temp[i + x][j + y].rgbtGreen;
                    blue += temp[i + x][j + y].rgbtBlue;
                }
            }
            // the current pixel will have the average of all pixels 1 pixel apart.
            image[i][j].rgbtRed = round(red / pixel_nr);
            image[i][j].rgbtGreen = round(green / pixel_nr);
            image[i][j].rgbtBlue = round(blue / pixel_nr);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // same as before, copy the original
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // the sobel matrix is basically a vector [1, 2, 1] multiplied by three values [-1, 0, 1]
            int sobel[] = {1, 2, 1};
            // we create Gx and Gy to store the sum of all different channels
            // index 0 = red; index 1 = green; index 2 = blue.
            int Gx[] = {0, 0, 0};
            int Gy[] = {0, 0, 0};

            // calculate Gx. starting at -1 ensures we can use the iteration to also generate the sobel matrix
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // avoid out of bounds possibilities
                    if (i + y < 0 || i + y > height - 1 || j + x < 0 || j + x > width - 1)
                    {
                        // note that, in this case, skipping a pixel will treat it as a black pixel,as intended
                        continue;
                    }
                    // adds all the channels multiplied by their corresponding value in the sobel matrix
                    // x will vary between -1, 0 and 1, generating the sobel matrix when multiplied by the sobel vector.
                    // note here we iterate over columns and then rows, to generate the Gx matrix
                    // sobel index is y + 1 because y starts at -1 and the sobel array at 0.
                    Gx[0] += temp[i + y][j + x].rgbtRed * x * sobel[y + 1];
                    Gx[1] += temp[i + y][j + x].rgbtGreen * x * sobel[y + 1];
                    Gx[2] += temp[i + y][j + x].rgbtBlue * x * sobel[y + 1];
                }
            }

            // calculate Gy. starting at -1 ensure we can use the iteration to also generate the sobel matrix
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (i + a < 0 || i + a > height - 1 || j + b < 0 || j + b > width - 1)
                    {
                        // note that in this case, skipping a pixel will treat it as a black pixel,as intended
                        continue;
                    }
                    // adds all the channels multiplied by their corresponding value in the sobel matrix
                    // a will vary between -1, 0 and 1, generating the sobel matrix.
                    // note here we iterate over rows and then columns, to generate the Gy matrix
                    // sobel index is b + 1 because b starts at -1 and the sobel array at 0.
                    Gy[0] += temp[i + a][j + b].rgbtRed * a * sobel[b + 1];
                    Gy[1] += temp[i + a][j + b].rgbtGreen * a * sobel[b + 1];
                    Gy[2] += temp[i + a][j + b].rgbtBlue * a * sobel[b + 1];
                }
            }

            // computes the value for each channel according to Sobel's operation
            int sobel_red = round(sqrt(pow(Gx[0], 2) + pow(Gy[0], 2)));
            int sobel_green = round(sqrt(pow(Gx[1], 2) + pow(Gy[1], 2)));
            int sobel_blue = round(sqrt(pow(Gx[2], 2) + pow(Gy[2], 2)));

            // caps the maximum value for each channel at 255
            image[i][j].rgbtRed = (sobel_red > 255) ? 255 : sobel_red;
            image[i][j].rgbtGreen = (sobel_green > 255) ? 255 : sobel_green;
            image[i][j].rgbtBlue = (sobel_blue > 255) ? 255 : sobel_blue;
        }
    }
    return;
}
