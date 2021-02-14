// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// defines a byte as 8 bits
typedef uint8_t BYTE;
// defines a audio sample (WAV) as having 16 bits.
typedef int16_t WAV_SAMPLE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(header, sizeof(BYTE), HEADER_SIZE, output);
    // TODO: Read samples from input file and write updated data to output file
    WAV_SAMPLE sample;
    while (fread(&sample, sizeof(WAV_SAMPLE), 1, input))
    {
        sample *= factor;
        fwrite(&sample, sizeof(WAV_SAMPLE), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
