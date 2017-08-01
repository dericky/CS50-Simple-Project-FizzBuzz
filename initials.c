#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void){
    string input = get_string();
    char tmp = ' ';
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == ' '){
            tmp = input[i];
        }
        else{
            if(tmp == ' '){
                printf("%c",toupper(input[i]));
                tmp = input[i];
            }
        }
    }
    printf("\n");
}