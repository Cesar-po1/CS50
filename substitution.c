#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int key (string argv[]);
string convertor (string text, string key[]); //declarations of functions

int main (int argc, string argv[]) //main
{
    if (argc < 2) //if the program receives less than 2 arguments
    {
        printf("The program neads 2 command-lines\n");
        return 1;
    }
    else if (argc > 2) //if the program receives more than 2 arguments
    {
        printf("The program reads only 2 command-lines\n");
        return 1;
    }
    else if (argc == 2) //receives 2 arguments
    {
        if (key(argv) == 1) //if key invalid
        {
            return 1;
        }
        else if (key(argv) == 0) //if valid key
        {
            string plaintext = get_string("Plaintext: "); //gets plaintext
            
            if (convertor(plaintext, argv) == 0) //if ciphertext works
            {
                return 0; //finish ok
            }
            else //if any error
            {
                printf("Error");
                return 1; //finish wrong
            }
        }
    }
    else
    {
        printf("Try again\n"); //anyother escenario 
        return 1; //finish wrong
    }
}

int key (string argv[]) //validates key
{
    int lenght = 0;
    
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        lenght ++; //sums one to the lenght of my key
        {
            if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') | (argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
            {  }
            else
            {
                printf("Error en caracter\n");  //if the key has a non-alphabetic char
                return 1;
            }
        }
    }
    if (lenght < 27 && lenght > 25) //checks correct lenght
    {
        for (int i = 0; argv[1][i] != '\0'; i++) 
        {
            if (argv[1][i] >= 97)  //if char minuscula convertir a mayuscula
            {
                argv[1][i] -= 32;  //cambia minusculas a mayusculas para verificar que no se repitan
            }
        }
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            for (int j = 0;argv[1][j] != '\0'; j++) //fors to verify no repeted letters
            {
                if (i == j+1)
                {
                    break;  //same character doesnt cancel
                }
                else if (argv[1][i] == argv[1][j+1]) //verifies if letter is repeted
                {
                    return 1;  //finds duplicated letter
                }
                else if (argv[1][i] != argv[1][j+1])
                {
                      //code works good! Your key is correct
                }
            }
        }
        return 0;
    }
    else
    {
        printf("Error en lenght\n");
        return 1;   //if lenght is not correct
    }
return 1;  //any other escenario
}

string convertor (string text, string key[]) //function to cipher
{
    int lenght = 0;
    printf("");
    for (int i = 0; key[1][i] != '\0'; i++) //loop to check the lenght of the text to cipher
    {
        lenght ++;
    }
    
    string encrypted[lenght]; //declared the lenght of the text to cipher
    
    for (int i = 0; text[i] != '\0'; i++) //for to to change every letter of my text
    {
        
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            encrypted[0][i] =key[1][text[i]-65]; //adds the ciphered letter to the sentence
        }
        else if (text[i] >= 'a' && text[i] <= 'z') //checks if char of text is a small letter
        {
            key[1][text[i]-97] = tolower(key[1][text[i]-97]); //converts the key to small to keep the same format
            encrypted[0][i] = key[1][text[i]-97]; //adds the ciphered letter to the sentence
        }
        else if (text[i] == '\0')
        {
            encrypted[0][i] = '\0';
        }
        else
        {
            encrypted[0][i] = text[i];  //does nothing to any non-alphabetic char
        }
    }
    //encrypted[0][lenght] = '\0';
    //printf("%s\n",encrypted[0]);
    printf("ciphertext: ");
    for (int i = 0;encrypted[0][i] != '\0';i++)
    {
        printf("%i",i);
        if (encrypted[0][i] >= 0 && encrypted[0][i] <= 126)
        {
            
            printf("%c\n",encrypted[0][i]);
        }
        else
        {
            break;
        }
    }
    printf("\n");
    return 0;
}