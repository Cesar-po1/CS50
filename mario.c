#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {    
        height = get_int("Height? \n"); //asks for the height of the leaders
    }
    while (height < 1 || height > 8);  //repeat if height is not between 1 and 8

    for(int i = 0; i < height ; i++)  //loop for lines
    {
        for(int j = height-1; j > -1 ; j--)  // loop for columns left side
        {
            if (i < j)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        {
            printf("  ");  //space between each side
        }
        for(int j = 0; j < height ; j++)   // loops for columns right side
        {
            if (i >= j)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

