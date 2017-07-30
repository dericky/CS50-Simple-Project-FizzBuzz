#include <stdio.h>
#include <cs50.h>
//This is a script to make the half pyramids like in Mario.

void generatePyramid(int height){
    
    int blank_space = height-1;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < blank_space; i++){
            printf(" ");
        }
        blank_space--;
        for(int k = height-blank_space-1; k > 0; k--){
            printf("#");
        }
        printf("  ");
        for(int a = 1; a < height-blank_space; a++){
            printf("#");
        }
        
        printf("\n");
    }
}

int main(void){
    int pyramid_height = -1;
    while(pyramid_height < 0 || pyramid_height > 23)
    {
        printf("Height: ");
        pyramid_height = get_int();
    }
    generatePyramid(pyramid_height);
   
}


