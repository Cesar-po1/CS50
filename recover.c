/* read data from a card, and extract JPEG data individually, and saved into divided file */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) // condition check if the command-line argument is only 1
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *inptrfile = fopen(argv[1], "r");
    if (!inptrfile)
    {
        printf("File can't be open correctly\n");
        return 1;
    }

    // repeat reading 512B from the input file
    BYTE *temp = malloc(512 * sizeof(BYTE)); //  buffer for input file
    char optfilename[8]; // for storing output file name
    int number = 0; // for digit part of the filename
    int endofile = 0; // initialize mark of end of the input file
    FILE *outputfile = NULL;

    do
    {
        if (temp == NULL) // check if the memory is leak or not
        {
            return 1;
        }
        // read first FAT block into temp
        endofile = fread(temp, sizeof(BYTE), 512, inptrfile);  // set the ending mark to be the return value of fread function
        // printf("temp1= %hhu, temp2 = %hhu, temp3 = %hhu, temp4 = %hhu\n", temp[0], temp[1], temp[2], temp[3]); //debug
        // read the first 4 bytes of the temp point and check if the first 4 bytes is the signature is JPEG
        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && (temp[3] & 0xf0) == 0xe0)
        {
            if (number != 0)
            {
                fclose(outputfile);
            }
            sprintf(optfilename, "%03i.jpeg", number); // generate a new output file

            outputfile = fopen(optfilename, "w"); // open a file for writing
            if (outputfile == NULL)
            {
                return 1;
            }
            fwrite(temp, sizeof(BYTE), 512, outputfile); // put the temp value into the opened file

            number = number + 1; // number increase as to increas the image file name
        } // end of if
        else if (number != 0) // start writing until detect new jpeg signature
        {
            fwrite(temp, sizeof(BYTE), 512, outputfile); // write to the output file if the temp contains no jpeg signature
        } //end else if

    }while (endofile == 512);  // end of while loop

    free(temp); // free malloc for temp
} // end of main
