#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    long card;

    card = get_long("What's your card number? \n");  //asks for a credit card
    
    if (card < 1000000000000 || card > 10000000000000000) //validates valid lenght
    {
        printf("INVALID\n");
        exit(0); //finishes program
    }
    
    long card_len = card;
    int lenght_card_number = 0;
    
    while (card_len != 0) //loop to count digits in card
    {
        card_len = card_len / 10;
        lenght_card_number++;
    }
    
    int digit2 = ((card % 100) / 10) * 2; //gets the second to last digit and multiplies it by two
    int digit4 = ((card % 10000) / 1000) * 2;
    int digit6 = ((card % 1000000) / 100000) * 2;
    int digit8 = ((card % 100000000) / 10000000) * 2;
    int digit10 = ((card % 10000000000) / 1000000000) * 2;
    int digit12 = ((card % 1000000000000) / 100000000000) * 2;
    int digit14 = ((card % 100000000000000) / 10000000000000) * 2;
    int digit16 = ((card % 10000000000000000) / 1000000000000000) * 2;
    
    int sum1 = + (digit2 % 10) + (digit2 % 100) / 10; //adds each digit of the numbers previously selected
    sum1 += (digit4 % 10) + (digit4 % 100) / 10;
    sum1 += (digit6 % 10) + (digit6 % 100) / 10;
    sum1 += (digit8 % 10) + (digit8 % 100) / 10;
    sum1 += (digit10 % 10) + (digit10 % 100) / 10;
    sum1 += (digit12 % 10) + (digit12 % 100) / 10;
    sum1 += (digit14 % 10) + (digit14 % 100) / 10;
    sum1 += (digit16 % 10) + (digit16 % 100) / 10;
    
    int digit1 = card % 10; //gets the digits not selected previously
    int digit3 = (card % 1000) / 100 ;
    int digit5 = (card % 100000) / 10000;
    int digit7 = (card % 10000000) / 1000000;
    int digit9 = (card % 1000000000) / 100000000;
    int digit11 = (card % 100000000000) / 10000000000;
    int digit13 = (card % 10000000000000) / 1000000000000;
    int digit15 = (card % 1000000000000000) / 100000000000000;
    
    int sum2 = digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13 + digit15; //adds the digit that were not added previously
     
    int sumTOT = sum1 + sum2; //adds the first sum and the second sum
    
    int card_start = card / pow(10, (lenght_card_number - 2)); //gets the first 2 digits of the credit card number
    
    if ((sumTOT % 10) != 0) //if the last digit of sumTOT is not 0 then the card is invalid
    {
        printf("INVALID\n");
        exit(0);
    }
    else if (card_start == 34 || card_start == 37) //checks requierments for amex
    {
        if (lenght_card_number == 15)
        {
            printf("AMEX\n");
        }
    }
    else if (card_start == 51 || card_start == 52 || card_start == 53 || card_start == 54
             || card_start == 55) //checks requierments for mastercard
    {
        if (lenght_card_number == 16)
        {
            printf("MASTERCARD\n");
        }
    }
    else if ((card_start / 10) == 4) //checks requierments for visa
    {
        if (lenght_card_number == 13 || lenght_card_number == 14 || lenght_card_number == 15 || lenght_card_number == 16)
        {
            printf("VISA\n");
        }
    }
    else //any other case is a invalid card
    {
        printf("INVALID\n");
        exit(0);
    }
}