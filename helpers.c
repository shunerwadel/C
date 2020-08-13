// Functions used to apply filters to BMP image files
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Look in each row
    for (int i = 0; i < height; i++)
    {
        // Look in each column
        for (int j = 0; j < width; j++)
        {
            // Calc ave value of RGB
            RGBTRIPLE pixel = image[i][j];
            float sum_RGB = (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue);
            float ave_RGB = round(sum_RGB / 3);

            // Assign ave to RGB in pixel
            pixel.rgbtRed = ave_RGB;
            pixel.rgbtGreen = ave_RGB;
            pixel.rgbtBlue = ave_RGB;
            image[i][j] = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Look in each row
    for (int i = 0; i < height; i++)
    {
        // Look in each column
        for (int j = 0; j < width; j++)
        {
            // Declare variables
            RGBTRIPLE pixel = image[i][j];
            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;

            // Apply red sepia filter
            float Red = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;

            if (Red > 255)
            {
                pixel.rgbtRed = 255;
            }
            else
            {
                pixel.rgbtRed = round(Red);
            }

            // Apply green sepia filter
            float Green = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;

            if (Green > 255)
            {
                pixel.rgbtGreen = 255;
            }
            else
            {
                pixel.rgbtGreen = round(Green);
            }

            // Apply blue sepia filter
            float Blue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            if (Blue > 255)
            {
                pixel.rgbtBlue = 255;
            }
            else
            {
                pixel.rgbtBlue = round(Blue);
            }

            // Assign ave to RGB in pixel
            image[i][j] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Look in each row
    for (int i = 0; i < height; i++)
    {
        // Look in each column
        for (int j = 0; j < width / 2; j++)
        {
            // Declare variables
            RGBTRIPLE pixelLeft = image[i][j];
            RGBTRIPLE pixelRight = image[i][width - j - 1];
            RGBTRIPLE temp;

            // Swap left and right
            temp = pixelLeft;
            image[i][j] = pixelRight;
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp image
    RGBTRIPLE temp_image[height][width];

    // Look in each row
    for (int i = 0; i < height; i++)
    {
        // Look in each column
        for (int j = 0; j < width; j++)
        {
            // Corner cases
            if (i == 0 && j == 0)
            {
                RGBTRIPLE leftTop;

                float sum_red = (image[0][0].rgbtRed + image[1][0].rgbtRed + image[0][1].rgbtRed + image[1][1].rgbtRed);

                leftTop.rgbtRed = round(sum_red / 4);

                float sum_green = (image[0][0].rgbtGreen + image[1][0].rgbtGreen + image[0][1].rgbtGreen + image[1][1].rgbtGreen);

                leftTop.rgbtGreen = round(sum_green / 4);

                float sum_blue = (image[0][0].rgbtBlue + image[1][0].rgbtBlue + image[0][1].rgbtBlue + image[1][1].rgbtBlue);

                leftTop.rgbtBlue = round(sum_blue / 4);

                temp_image[i][j] = leftTop;

                continue;
            }
            else if (i == height - 1 && j == 0)
            {
                RGBTRIPLE leftBot;

                float sum_red = (image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed + image[height - 1][1].rgbtRed
                                 + image[height - 2][1].rgbtRed);

                leftBot.rgbtRed = round(sum_red / 4);

                float sum_green = (image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen + image[height - 1][1].rgbtGreen
                                   + image[height - 2][1].rgbtGreen);

                leftBot.rgbtGreen = round(sum_green / 4);

                float sum_blue = (image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue + image[height - 1][1].rgbtBlue
                                  + image[height - 2][1].rgbtBlue);

                leftBot.rgbtBlue = round(sum_blue / 4);

                temp_image[i][j] = leftBot;

                continue;
            }
            else if (i == 0 && j == width - 1)
            {
                RGBTRIPLE rightTop;

                float sum_red = (image[0][width - 1].rgbtRed + image[1][width - 1].rgbtRed + image[0][width - 2].rgbtRed
                                 + image[1][width - 2].rgbtRed);

                rightTop.rgbtRed = round(sum_red / 4);

                float sum_green = (image[0][width - 1].rgbtGreen + image[1][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen
                                   + image[1][width - 2].rgbtGreen);

                rightTop.rgbtGreen = round(sum_green / 4);

                float sum_blue = (image[0][width - 1].rgbtBlue + image[1][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue
                                  + image[1][width - 2].rgbtBlue);

                rightTop.rgbtBlue = round(sum_blue / 4);

                temp_image[i][j] = rightTop;


                continue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                RGBTRIPLE rightBot;

                float sum_red = (image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed
                                 + image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed);

                rightBot.rgbtRed = round(sum_red / 4);

                float sum_green = (image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen
                                   + image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen);

                rightBot.rgbtGreen = round(sum_green / 4);

                float sum_blue = (image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue
                                  + image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue);

                rightBot.rgbtBlue = round(sum_blue / 4);

                temp_image[i][j] = rightBot;

                continue;
            }
            // Top edge, non-corner case
            else if (i == 0)
            {
                // Declare variables
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE sideLeft = image [i][j - 1];
                RGBTRIPLE sideRight = image [i][j + 1];
                RGBTRIPLE botLeft = image [i + 1][j - 1];
                RGBTRIPLE botMid = image [i + 1][j];
                RGBTRIPLE botRight = image [i + 1][j + 1];

                // Calc average
                float sum_red = (pixel.rgbtRed + sideLeft.rgbtRed + sideRight.rgbtRed + botLeft.rgbtRed + botMid.rgbtRed
                                 + botRight.rgbtRed);

                temp_image[i][j].rgbtRed = round(sum_red / 6);

                float sum_green = (pixel.rgbtGreen + sideLeft.rgbtGreen + sideRight.rgbtGreen + botLeft.rgbtGreen + botMid.rgbtGreen
                                   + botRight.rgbtGreen);

                temp_image[i][j].rgbtGreen = round(sum_green / 6);

                float sum_blue = (pixel.rgbtBlue + sideLeft.rgbtBlue + sideRight.rgbtBlue + botLeft.rgbtBlue + botMid.rgbtBlue
                                  + botRight.rgbtBlue);

                temp_image[i][j].rgbtBlue = round(sum_blue / 6);

                continue;
            }
            // Bottom edge, non-corner case
            else if (i == height - 1)
            {
                // Declare variables
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE topLeft = image [i - 1][j - 1];
                RGBTRIPLE topMid = image [i - 1][j];
                RGBTRIPLE topRight = image [i - 1][j + 1];
                RGBTRIPLE sideLeft = image [i][j - 1];
                RGBTRIPLE sideRight = image [i][j + 1];

                // Calc average
                float sum_red = (pixel.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed + sideLeft.rgbtRed
                                 + sideRight.rgbtRed);

                temp_image[i][j].rgbtRed = round(sum_red / 6);

                float sum_green = (pixel.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen + sideLeft.rgbtGreen
                                   + sideRight.rgbtGreen);

                temp_image[i][j].rgbtGreen = round(sum_green / 6);

                float sum_blue = (pixel.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue + sideLeft.rgbtBlue
                                  + sideRight.rgbtBlue);

                temp_image[i][j].rgbtBlue = round(sum_blue / 6);

                continue;
            }
            // Left edge, non-corner case
            else if (j == 0)
            {
                // Declare variables
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE topMid = image [i - 1][j];
                RGBTRIPLE topRight = image [i - 1][j + 1];
                RGBTRIPLE sideRight = image [i][j + 1];
                RGBTRIPLE botMid = image [i + 1][j];
                RGBTRIPLE botRight = image [i + 1][j + 1];

                // Calc average
                float sum_red = (pixel.rgbtRed + topMid.rgbtRed + topRight.rgbtRed + sideRight.rgbtRed + botMid.rgbtRed
                                 + botRight.rgbtRed);

                temp_image[i][j].rgbtRed = round(sum_red / 6);

                float sum_green = (pixel.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen + sideRight.rgbtGreen + botMid.rgbtGreen
                                   + botRight.rgbtGreen);

                temp_image[i][j].rgbtGreen = round(sum_green / 6);

                float sum_blue = (pixel.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue + sideRight.rgbtBlue + botMid.rgbtBlue
                                  + botRight.rgbtBlue);

                temp_image[i][j].rgbtBlue = round(sum_blue / 6);

                continue;
            }
            // Right edge, non-corner case
            else if (j == width - 1)
            {
                //Declare variables
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE topLeft = image[i - 1][j - 1];
                RGBTRIPLE topMid = image[i - 1][j];
                RGBTRIPLE sideLeft = image[i][j - 1];
                RGBTRIPLE botLeft = image[i + 1][j - 1];
                RGBTRIPLE botMid = image[i + 1][j];

                // Calc average
                float sum_red = (pixel.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed + sideLeft.rgbtRed + botLeft.rgbtRed
                                 + botMid.rgbtRed);

                temp_image[i][j].rgbtRed = round(sum_red / 6);

                float sum_green = (pixel.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + sideLeft.rgbtGreen + botLeft.rgbtGreen
                                   + botMid.rgbtGreen);

                temp_image[i][j].rgbtGreen = round(sum_green / 6);

                float sum_blue = (pixel.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + sideLeft.rgbtBlue + botLeft.rgbtBlue
                                  + botMid.rgbtBlue);

                temp_image[i][j].rgbtBlue = round(sum_blue / 6);

                continue;
            }
            // Non-edge case
            else
            {
                //Declare variables
                RGBTRIPLE pixel = image[i][j];
                RGBTRIPLE topLeft = image[i - 1][j - 1];
                RGBTRIPLE topMid = image[i - 1][j];
                RGBTRIPLE topRight = image[i - 1][j + 1];
                RGBTRIPLE sideLeft = image[i][j - 1];
                RGBTRIPLE sideRight = image[i][j + 1];
                RGBTRIPLE botLeft = image[i + 1][j - 1];
                RGBTRIPLE botMid = image[i + 1][j];
                RGBTRIPLE botRight = image[i + 1][j + 1];

                // Calc average
                float sum_red = (pixel.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed + sideLeft.rgbtRed
                                 + sideRight.rgbtRed + botLeft.rgbtRed + botMid.rgbtRed + botRight.rgbtRed);

                temp_image[i][j].rgbtRed = round(sum_red / 9);

                float sum_green = (pixel.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen + sideLeft.rgbtGreen
                                   + sideRight.rgbtGreen + botLeft.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen);

                temp_image[i][j].rgbtGreen = round(sum_green / 9);

                float sum_blue = (pixel.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue + sideLeft.rgbtBlue
                                  + sideRight.rgbtBlue + botLeft.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue);

                temp_image[i][j].rgbtBlue = round(sum_blue / 9);

                continue;
            }
        }
    }

    // Assign temp image as image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }
    return;
}
