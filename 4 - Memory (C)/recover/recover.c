//https://cs50.harvard.edu/x/2021/psets/4/recover/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// defines the size of a byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("File can't be read.\n");
        return 1;
    }

    // JPG are stored in blocks of 512 bytes
    unsigned char buffer[512];
    // a counter for the number of files
    int file_count = 0;

    // specified file names comprise of 8 characters
    // 3 digits, a dot, "jpg" and the string termination "/0"
    char filename[8];
    // creates the first file name "000.jpg"
    sprintf(filename, "%03i.jpg", file_count);

    // initializes the first image
    FILE *img = NULL;

    // while there are possible jpg blocks to read from
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // these characters mark the beginning of a jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if this is the first image found
            if (file_count == 0)
            {
                //create file with filname "000.jpg"
                img = fopen(filename, "w");
                // writes the contents
                fwrite(buffer, sizeof(BYTE), 512, img);
                // updates the number of images, and enables the condition for writing remaining blocks
                file_count++;
            }
            // if file count is not 0, then this is a new jpg file
            else
            {
                // we close the current image
                fclose(img);
                // update the file name
                sprintf(filename, "%03i.jpg", file_count);
                // the block below could be stored in a function: TO DO in future
                // create a new file
                img = fopen(filename, "w");
                //write
                fwrite(buffer, sizeof(BYTE), 512, img);
                //update count
                file_count++;
            }
        }
        // if it is not the beginning of a function and a jpg file has already been found, add this block to current file
        // note that this exercise's file specified all jpgs would be next to each other in the memory
        else if (file_count > 0)
        {
            // write the block to the current file
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    // Close file
    fclose(file);
}