#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (text[0] == '\0');
    
    float cont_l = 0;
    int letter;
    float cont_w = 1;
    float cont_s = 0;
    for (letter = 0; text[letter] != '\0'; letter ++) //reviews everyletter
    {
        if ((text[letter] >= 'a' && text[letter] <= 'z') | (text[letter] >= 'A' && text[letter] <= 'Z'))
        {
            cont_l ++; //letter counter
        } 
        
        if (text[letter] == ' ')
        {
            cont_w ++; //word counter
        }
        
        if (text[letter] == '.' | text[letter] == '!' | text[letter] == '?')
        {
            cont_s ++; //sentence counter
        }
    }

    float L = ((cont_l / cont_w) * 100); // average number of letters per 100 words in the text
    
    float S = ((cont_s / cont_w) * 100); //average number of sentences per 100 words in the text.
    
    float grade = (0.0588 * L - 0.296 * S - 15.8); //Coleman-Liau formula
    
    if (grade >= 16)     // printer of grades
    {
        printf("Grade 16+\n");
    }
    else if (grade < 16 && grade >= 1)
    {
        printf("Grade %.0f \n", round(grade));
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    
}