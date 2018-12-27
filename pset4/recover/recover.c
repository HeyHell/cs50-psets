#include <stdio.h>

// size of one block
#define SIZE 512

// define a term BYTE
typedef unsigned char BYTE;

void recover(FILE*);

// main: recover jpeg images by given memory card
int main(int argc, char *argv[])
{
    // check the correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover card\n");
        return 1;
    }

    // try file card
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        fprintf(stderr, "file can't be open\n");
        return 2;
    }

    // recover images
    recover(card);
}

// recover: recover all JPEG images by memory card
void recover(FILE *card)
{
    int count = 0;     // number of file
    BYTE buffer[SIZE]; // temporary storage bytes from card
    char filename[8];  // file name
    FILE *img = NULL;  // JPEG image

    // read the entire card to the end
    while (fread(buffer, sizeof(BYTE), SIZE, card) == SIZE)
    {
        // found new JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // write new name
            sprintf(filename, "%03i.jpg", count);
            // close previous file
			if (img)
                fclose(img);
            // create new file with new name
            img = fopen(filename, "w");
            // change next file number
            count++;
        }
        // already found JPEG
		if (img)
            fwrite(buffer, SIZE, 1, img);
    }

    // close files
	if (img)
        fclose(img);
    fclose(card);
}