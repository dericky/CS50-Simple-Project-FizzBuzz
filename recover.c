
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t  BYTE;
bool isJpg(char *block){
    BYTE byte = block[0];
    if(byte == 0xff){
        byte = block[1];
        if(byte == 0xd8){
            byte = block[2];
            if(byte == 0xff){
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ./recover <filename>\n");
        return 1;
    }
    

    char *input = argv[1];

    // open input file borrowed from copy.c
    FILE *inputFile = fopen(input, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", input);
        return 2;
    }
    char block[512]; // 512 byte 'blocks'
    //BYTE firstByte;
    int fileCounter = -1;
    char fileName[255];
    FILE *output = NULL;
    
    while(fread(&block, 1, 512, inputFile) == 512){
        
       if(isJpg(block)){
                    //start of jpg
                    if(output)
                        fclose(output);
                    fileCounter++;
                    sprintf(fileName, "%03i.jpg", fileCounter);
                    output = fopen(fileName, "w");
                    fwrite(&block, 1, 512, output);
                    
                    printf("File Num: %i\n", fileCounter);
        }
        else{
            if(fileCounter > -1){
                    fwrite(&block, 1, 512, output);
            }
        }
    }
    if(output)
    fclose(output);
    
    return 0;
}