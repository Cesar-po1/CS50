#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n ");  //asks name
    printf("hello, %s, have a good day\n", name); //prints sentence
}