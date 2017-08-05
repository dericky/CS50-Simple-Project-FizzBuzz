/**
 * Resize a bmp, code from copy.c modified
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }
    if(atoi(argv[1]) <= 0 || atoi(argv[1]) > 100)
    {
        fprintf(stderr, "Factor size invalid\n");
        return 5;
    }
    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }
    
    BITMAPINFOHEADER biResized = bi;
    BITMAPFILEHEADER bfResized = bf;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    biResized.biWidth *= n;
    biResized.biHeight *= n;
    int padding2 = (4 - (biResized.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    biResized.biSizeImage = ((sizeof(RGBTRIPLE) * biResized.biWidth) + padding2) * abs(biResized.biHeight);
    bfResized.bfSize = biResized.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResized, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResized, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE scanLine[bi.biWidth][abs(bi.biHeight)];
    //RGBTRIPLE scanLineHeight[biResized.biHeight];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            scanLine[j][i] = triple;
            //printf("Red: %i, Green: %i, Blue: %i\n", scanLine[j][i].rgbtRed,scanLine[j][i].rgbtGreen,scanLine[j][i].rgbtBlue );
          //  printf("J: %i, I: %i\n", j, i);
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    for(int height = 0; height < abs(bi.biHeight); height++){
        for(int twice = 0; twice < n; twice++){
            for(int width = 0; width < bi.biWidth; width++){
                for(int twice2 = 0; twice2 < n; twice2++){
                   // printf("New: Red: %i, Green: %i, Blue: %i\n", scanLine[width][height].rgbtRed, scanLine[width][height].rgbtGreen, scanLine[width][height].rgbtBlue);
                    fwrite(&scanLine[width][height], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
