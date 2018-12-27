// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize size infile outfile\n");
        return 1;
    }

    // get size multiplier
    int n = atoi(argv[1]);
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Invalid size %i.\n", n);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 2;
    }

    // remember width (iWidth) and height (iHeight) of the input file
    int iWidth = bi.biWidth;
    int iHeight = abs(bi.biHeight);

    // determine padding of input file for scanlines
    int ipadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify width and height for output file
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding of output file for scanlines
    int opadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify size for output file
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + opadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < iHeight; i++)
    {
        // resize vertically
        for (int col = 0; col < n; col++)
        {
            // resize horizontally
            for (int row = 0; row < iWidth; row++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int j = 0; j < n; j++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // return cursor back
            fseek(inptr, -iWidth * sizeof(RGBTRIPLE), SEEK_CUR);

            // add padding for output file, if any
            for (int p = 0; p < opadding; p++)
                fputc(0x00, outptr);
        }

        // skip over scanlines
        fseek(inptr, iWidth * sizeof(RGBTRIPLE) + ipadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
