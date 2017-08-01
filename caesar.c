#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


void getCipher(string input, int key){
    if(strlen(input)>0){
        for(int i = 0; i < strlen(input); i++){
            char letter = input[i];
            if(isalpha(letter)){
                if(isupper(letter)){
                    letter -= 65;
                    letter += key;
                    letter %= 26;
                    letter += 65;
                    printf("%c", letter);  
                }
                else if(islower(letter)){
                    letter -= 97;
                    letter += key;
                    letter %= 26;
                    letter += 97;
                    printf("%c", letter); 
                }
            }
            else
                printf("%c", letter); 
        }
    }
    printf("\n"); 
}


int main(int argc, string argv[]){
    if(argc == 2){
        if(atoi(argv[1]) > 0){
            printf("plaintext: ");
            string input = get_string();
            printf("ciphertext: ");
            getCipher(input,atoi(argv[1]));
            return 0;
        }
    }
    else{
        printf("Usage: ./caesar k\n");
        return 1;
    }
}