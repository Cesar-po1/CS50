#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (!file)
        {
            printf("File can't be open correctly\n");
            return 1;
        }
        BYTE *buffer = malloc(512 * sizeof(BYTE));
        char filename[8];
        FILE *img = NULL;
        int n = 0;
        int end = 0;
        
        do
        {
            if (buffer == NULL) // check if the memory is leak or not
            {
                return 1;
            }
            
            end = fread(buffer, sizeof(BYTE), 512, file);
            
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (n != 0)
                {
                    fclose(img);
                }
                
                sprintf(filename, "%03i.jpg",n);
                
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    return 1;
                }
                
                fwrite(buffer, sizeof(BYTE), 512, img);
                n++;
                printf("%i\n",n);
            }
            else if (n != 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        } 
        while (end == 512);
    
        free(buffer); 
    }
}
