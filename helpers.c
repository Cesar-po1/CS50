#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int promBnW = round(round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            
            image[i][j].rgbtRed = promBnW;
            image[i][j].rgbtGreen = promBnW;
            image[i][j].rgbtBlue = promBnW;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int tempGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int tempBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if (tempRed > 255)
            {
                tempRed = 255;
            }
            else if (tempRed < 0)
            {
                tempRed = 0;
            }
            
            if (tempGreen > 255)
            {
                tempGreen = 255;
            }
            else if (tempGreen < 0)
            {
                tempGreen = 0;
            }
            
            if (tempBlue > 255)
            {
                tempBlue = 255;
            }
            else if (tempBlue < 0)
            {
                tempBlue = 0;
            }
            image[i][j].rgbtRed = tempRed;
            image[i][j].rgbtGreen = tempGreen;
            image[i][j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            
            image[i][width - 1 - j].rgbtRed = tempRed;
            image[i][width - 1 - j].rgbtGreen = tempGreen;
            image[i][width - 1 - j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) //loop to copy image 
        {                               
            cimage[i][j] = image[i][j]; // to see the avg
        }
    }
    for (int i = 1; i < height - 1; i++) //center blur
    {
        for (int j = 1; j < width - 1; j++)
        {
            cimage[i][j].rgbtRed = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                                 image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                                 image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed 
                                                 + image[i + 1][j + 1].rgbtRed) / 9);
            
            cimage[i][j].rgbtGreen = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                   image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                                   image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                   image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);
            
            cimage[i][j].rgbtBlue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                  image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                                  image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + 
                                                  image[i + 1][j + 1].rgbtBlue) / 9);
        }
    }
    for (int i = 1; i < height - 1; i++) //loop for the edges left and right
    {
        cimage[i][0].rgbtRed = round((float)(image[i - 1][1].rgbtRed + image[i - 1][0].rgbtRed + //left edge red
                                             image[i][0].rgbtRed + image[i][1].rgbtRed + image[i + 1][1].rgbtRed + image[i + 1][0].rgbtRed) / 6);
            
        cimage[i][0].rgbtGreen = round((float)(image[i - 1][1].rgbtGreen + image[i - 1][0].rgbtGreen + //left edge green
                                               image[i][0].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen +
                                               image[i + 1][0].rgbtGreen) / 6);
        
        cimage[i][0].rgbtBlue = round((float)(image[i - 1][1].rgbtBlue + image[i - 1][0].rgbtBlue + //left edge blue
                                              image[i][0].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue +
                                              image[i + 1][0].rgbtBlue) / 6);

        cimage[i][width - 1].rgbtRed = round((float)(image[i - 1][width - 2].rgbtRed + //right edge red 
                                             image[i - 1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i][width - 2].rgbtRed +
                                             image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed) / 6);
            
        cimage[i][width - 1].rgbtGreen = round((float)(image[i - 1][width - 2].rgbtGreen + //right edge green
                                               image[i - 1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen +
                                               image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen) / 6);
        
        cimage[i][width - 1].rgbtBlue = round((float)(image[i - 1][width - 2].rgbtBlue + //right edge blue
                                              image[i - 1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue +
                                              image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue) / 6);
    }
    for (int j = 1; j < width - 1; j++) //loop top and bottom row
    {
        cimage[0][j].rgbtRed = round((float)(image[1][j - 1].rgbtRed + image[0][j - 1].rgbtRed + //top red
                                             image[0][j].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed + image[0][j + 1].rgbtRed) / 6);
            
        cimage[0][j].rgbtGreen = round((float)(image[1][j -  1].rgbtGreen + image[0][j - 1].rgbtGreen + //top green
                                               image[0][j].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen +
                                               image[0][j + 1].rgbtGreen) / 6);
            
        cimage[0][j].rgbtBlue = round((float)(image[1][j - 1].rgbtBlue + image[0][j - 1].rgbtBlue + //top blue
                                              image[0][j].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue + image[0][j + 1].rgbtBlue) / 6);
            
        cimage[height - 1][j].rgbtRed = round((float)(image[height - 2][j - 1].rgbtRed + //bottom red
                                              image[height - 2][j].rgbtRed + image[height - 2][j + 1].rgbtRed + image[height - 1][j - 1].rgbtRed +
                                              image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed) / 6);
            
        cimage[height - 1][j].rgbtGreen = round((float)(image[height - 2][j - 1].rgbtGreen + image[height - 2][j].rgbtGreen + //bottom green
                                                image[height - 2][j + 1].rgbtGreen + image[height - 1][j - 1].rgbtGreen +
                                                image[height - 1][j].rgbtGreen +
                                                image[height - 1][j + 1].rgbtGreen) / 6);
        
        cimage[height - 1][j].rgbtBlue = round((float)(image[height - 2][j - 1].rgbtBlue + image[height - 2][j].rgbtBlue + //bottom blue
                                               image[height - 2][j + 1].rgbtBlue + image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue +
                                               image[height - 1][j + 1].rgbtBlue) / 6);
    }  
    
    // CHANGES CORNERS
    
    cimage[0][0].rgbtRed = round((float)(image[0][0].rgbtRed + image[0][1].rgbtRed +    //left top corner
                                         image[1][0].rgbtRed + image[1][1].rgbtRed) / 4);
    cimage[0][0].rgbtGreen = round((float)(image[0][0].rgbtGreen + image[0][1].rgbtGreen +
                                           image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4);
    cimage[0][0].rgbtBlue = round((float)(image[0][0].rgbtBlue + image[0][1].rgbtBlue +
                                          image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4);
    
    cimage[height - 1][0].rgbtRed = round((float)(image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed + //bottom left
                                          image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed) / 4);
    cimage[height - 1][0].rgbtGreen = round((float)(image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen +
                                            image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen) / 4);
    cimage[height - 1][0].rgbtBlue = round((float)(image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue +
                                           image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue) / 4);
    
    cimage[0][width - 1].rgbtRed = round((float)(image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + //right top
                                         image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed) / 4);
    cimage[0][width - 1].rgbtGreen = round((float)(image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + 
                                           image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen) / 4);
    cimage[0][width - 1].rgbtBlue = round((float)(image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue +
                                          image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue) / 4);
    
    cimage[height - 1][width - 1].rgbtRed = round((float)(image[height - 1][width - 1].rgbtRed +
                                            image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + //right bottom
                                            image[height - 2][width - 2].rgbtRed) / 4);
    cimage[height - 1][width - 1].rgbtGreen = round((float)(image[height - 1][width - 1].rgbtGreen +
            image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen +
            image[height - 2][width - 2].rgbtGreen) / 4);
    cimage[height - 1][width - 1].rgbtBlue = round((float)(image[height - 1][width - 1].rgbtBlue +
            image[height - 2][width - 1].rgbtBlue +
            image[height - 1][width - 2].rgbtBlue +
            image[height - 2][width - 2].rgbtBlue) / 4);
    
    for (int i = 0; i < height; i++) //changes the image to the blur image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = cimage[i][j];
        }
    }
    return;
}
