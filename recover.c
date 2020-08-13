// Program to parse through file and recover jpegs
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check if command line arguement given
    if (argc != 2)
    {
        printf("Useage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *infile = fopen(argv[1], "r");

    // Check if file is empty
    if (infile == NULL)
    {
        printf("Can not read file.\n");
        return 2;
    }

    // Declare variables
    int block_size = 512;
    int image = 0;
    bool in_progress = false;
    char *filename = malloc(7);
    FILE *outfile = NULL;

    // Allocate memory
    uint8_t *temp = malloc(block_size);

    if (temp == NULL)
    {
        printf("NULL pointer location\n");
        return 1;
    }

    // Read input file
    while (fread(temp, block_size, 1, infile) == 1)
    {
        // Check for jpeg
        if (*temp == 0xff && *(temp + 1) == 0xd8 && *(temp + 2) == 0xff && (*(temp + 3) & 0xf0) == 0xe0)
        {
            // Handle first case
            if (in_progress == false)
            {
                // Define new file name
                sprintf(filename, "%03i.jpg", image);
                image += 1;

                // Open new file
                outfile = fopen(filename, "w");

                // Write first block to file
                fwrite(temp, block_size, 1, outfile);

                // Set in progress to true
                in_progress = true;
            }
            else
            {
                // Stop outfile writing
                fclose(outfile);

                // Define new file name
                sprintf(filename, "%03i.jpg", image);
                image += 1;

                // Open new file
                outfile = fopen(filename, "w");

                // Write first block to file
                fwrite(temp, block_size, 1, outfile);
            }
        }
        else if (in_progress == true)
        {
            // Append block to current outfile
            fopen(filename, "a");

            // Write first block to file
            fwrite(temp, block_size, 1, outfile);
        }
    }
    // Free allocated memory
    free(temp);
    free(filename);

    return 0;
}
