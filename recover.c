
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) //checks if a file is given
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else if (argc == 2) //if a file is given
    {
        FILE *file = fopen(argv[1], "r"); //opens and reads given file
        if (!file) //if file damaged
        {
            printf("File can't be open correctly\n");
            return 1;
        }
        
        BYTE *buffer = malloc(512 * sizeof(BYTE)); //locks enough memory to store data
        char filename[8];
        FILE *img = NULL;
        int n = 0;
        int end = 0;
        
        while (fread(buffer, sizeof(BYTE), 512, file) == 512) //until no more data
        {
            if (buffer == NULL) // check if the memory is leak or not
            {
                return 1;
            }
    
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //checks for a jpg
            {
                if (n != 0) //if not first photo
                {
                    fclose(img);
                }
                
                sprintf(filename, "%03i.jpg", n); //assigns name to photo
                
                img = fopen(filename, "w"); //opens photo to write
                if (img == NULL) //leak or not
                {
                    return 1;
                }
                
                fwrite(buffer, sizeof(BYTE), 512, img); //writes image
                n++;
            }
            
            else if (n != 0) 
            {
                fwrite(buffer, sizeof(BYTE), 512, img); //continous writing image already started
            }
        } 
        
        // closes open files
        fclose(file);
        fclose(img); 
        
        //frees memory used
        free(buffer); 
        
        // correct return value
        return 0;
    }
}
