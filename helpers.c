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
            int promBnW = round(round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            
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
        for (int j = 0; j < width/2 ; j++)
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
    for (int i = 1; i < height - 1; i++) //center blur
    {
        for (int j = 1; j < width - 1; j++)
        {
            int red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed
            + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9);
            
            int green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen
            + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);
            
            int blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue
            + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue+ image[i + 1][j + 1].rgbtBlue) / 9);
            
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 1; i < height - 1; i++)
    {
        int edgeIR = round((image[i - 1][1].rgbtRed + image[i - 1][0].rgbtRed + image[i][0].rgbtRed + image[i][1].rgbtRed
            + image[i + 1][1].rgbtRed + image[i + 1][0].rgbtRed) / 6);
            
        int edgeIG = round((image[i - 1][1].rgbtGreen + image[i - 1][0].rgbtGreen + image[i][0].rgbtGreen + image[i][1].rgbtGreen
            + image[i + 1][1].rgbtGreen + image[i + 1][0].rgbtGreen) / 6);
        
        int edgeIB = round((image[i - 1][1].rgbtBlue + image[i - 1][0].rgbtBlue + image[i][0].rgbtBlue + image[i][1].rgbtBlue
            + image[i + 1][1].rgbtBlue + image[i + 1][0].rgbtBlue) / 6);
            
        image[i][0].rgbtRed = edgeIR;
        image[i][0].rgbtGreen = edgeIG;
        image[i][0].rgbtBlue = edgeIB;
            
        int edgeDR = round((image[i - 1][width - 2].rgbtRed + image[i - 1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i][width - 2].rgbtRed
            + image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed) / 6);
            
        int edgeDG = round((image[i - 1][width - 2].rgbtGreen + image[i - 1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen
            + image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen) / 6);
        
        int edgeDB = round((image[i - 1][width - 2].rgbtBlue + image[i - 1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue
            + image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue) / 6);
            
        image[i][width - 1].rgbtRed = edgeDR;
        image[i][width - 1].rgbtGreen = edgeDG;
        image[i][width - 1].rgbtBlue = edgeDB;
    }
    for (int j = 1; j < width - 1; j++)
    {
        int edgeUR = round((image[1][j - 1].rgbtRed + image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[1][j].rgbtRed
            + image[1][j + 1].rgbtRed + image[0][j + 1].rgbtRed) / 6);
            
        int edgeUG = round((image[1][j -  1].rgbtGreen + image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[1][j].rgbtGreen
            + image[1][j + 1].rgbtGreen + image[0][j + 1].rgbtGreen) / 6);
            
        int edgeUB = round((image[1][j - 1].rgbtBlue + image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[1][j].rgbtBlue
            + image[1][j + 1].rgbtBlue + image[0][j + 1].rgbtBlue) / 6);
            
        image[0][j].rgbtRed = edgeUR;
        image[0][j].rgbtGreen = edgeUG;
        image[0][j].rgbtBlue = edgeUB;
            
        int edgeAR = round((image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed + image[height][j - 1].rgbtRed
            + image[height][j].rgbtRed + image[height][j + 1].rgbtRed) / 6);
            
        int edgeAG = round((image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen + image[height][j - 1].rgbtGreen
            + image[height][j].rgbtGreen + image[height][j + 1].rgbtGreen) / 6);
        
        int edgeAB = round((image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue + image[height][j - 1].rgbtBlue
            + image[height][j].rgbtBlue + image[height][j + 1].rgbtBlue) / 6);
            
        image[height][j].rgbtRed = edgeAR;
        image[height][j].rgbtGreen = edgeAG;
        image[height][j].rgbtBlue = edgeAB;
    }  
    image[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed)/4);
    image[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen)/4);
    image[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue)/4);
    
    image[height - 1][0].rgbtRed = round((image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed + image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed)/4);
    image[height - 1][0].rgbtGreen = round((image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen + image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen)/4);
    image[height - 1][0].rgbtBlue = round((image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue + image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue)/4);
    
    image[0][width - 1].rgbtRed = round((image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed)/4);
    image[0][width - 1].rgbtGreen = round((image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen)/4);
    image[0][width - 1].rgbtBlue = round((image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue)/4);
    
    image[height - 1][width - 1].rgbtRed = round((image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed)/4);
    image[height - 1][width - 1].rgbtGreen = round((image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen)/4);
    image[height - 1][width - 1].rgbtBlue = round((image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue)/4);
    
    return;
}
