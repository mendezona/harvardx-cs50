#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //Open memory card
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //get memory card file name and make output file names
    char *infile = argv[1];

    //open memory card file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    BYTE buffer[513];//create buffer for 512 bytes
    int jpegCount = 0;//start naming at 0
    char *filename = malloc(sizeof(char) * 8);//save memory for naming of file
    sprintf(filename, "%03i.jpg", jpegCount);//get first name of JPEG
    FILE *outptr = fopen(filename, "w");//open output file with name frorm above

    while (fread(&buffer, sizeof(BYTE), 512, inptr) == 512)//iterate over memory card until it no longer return 512 bytes
    {
        fseek(inptr, -512, SEEK_CUR);//go back 512 bytes from the while loop
        fread(&buffer, sizeof(BYTE), 512, inptr);//read 512 bytes into buffer

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)//if header of 512 is a JPEG header
        {
            if (jpegCount > 0)//if not first JPEG
            {
                fclose(outptr);//close current output file
                sprintf(filename, "%03i.jpg", jpegCount);//get new name for next output file
                fopen(filename, "w");//open new output file with file name from above
            }

            fwrite(&buffer, sizeof(BYTE), 512, outptr);//write 512 bytes in buffer to output file
            jpegCount++;//update jpegCount for new name
        }

        else //if currernt 512 bytes in buffer does not have JPEG header do nothing unless...
        {
            //... JPEG was already found, in this case write this 512 bytes in buffer to current JPEG file until new header found
            if (jpegCount > 0) 
            {
                fwrite(&buffer, sizeof(BYTE), 512, outptr);//correct
            }
        }
    }

    free(filename);//free memory from filename
    return 0;
}