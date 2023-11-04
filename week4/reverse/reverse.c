#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("How to use: ./reverse input.wav output.wav \n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Impossible to open\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("File could not be open\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    const int block_size = get_block_size(header);
    // TODO #7

    // Write reversed audio to file
    // TODO #8

    BYTE reversed[block_size];
    fseek(input, 0, SEEK_END);
    while (ftell(input) > sizeof(header))
    {
        fseek(input, -1 * block_size, SEEK_CUR);
        fread(&reversed, block_size, 1, input);
        fwrite(&reversed, block_size, 1, output);
        fseek(input, -1 * block_size, SEEK_CUR);

    }

    //close file
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    const int length = 4;
    char array[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < length; i++)
    {
        if (header.format[i] != array[i])
        {
            printf("File is not WAV\n");
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int blocksize = header.numChannels * round((header.bitsPerSample / 8));
    return blocksize;
}