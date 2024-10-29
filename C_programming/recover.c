#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 
 // Number of btes in each block
 const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept only 1 command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open memory card
    FILE *card = fopen(argv[1], "r");

    // check that there is data to read from the card
    if (card = NULL)
    {
        printf("Card cannot be oppened for reading.");
        return 1;
    }

    // buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // pointer to output file
    FILE *img = NULL;

    // array for jpeg filename
    char filename[8];

    // number of images
    int img_count = 0;

    // While there's still data to be read from the card
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // check for image header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff))
        {
            if (buffer[3] >= 0xe0 && buffer[3] <= 0xef)
            {
                // if image found is not the first close open file and continue
                if (img_count > 0)
                {
                    fclose(img);
                }

                // give new jpeg filename
                sprintf(filename, "%03i.jpg", img_count);
                
                // open output file
                img = fopen(filename, "w");

                // error if file canot be created
                if (img == NULL)
                {
                    fprintf(stderr, "%s could not be created.", filename);
                    return 2;
                }

                // increment number of imge files
                img_count++;
            }
        }
        // write data to putput file if it exists
        if (img != NULL)
        {
            fwrite (buffer, BLOCK_SIZE, 1, img);
        }
    }
    // close last jpeg file
    fclose(img);

    // close card
    fclose(card);

    return 0;
}