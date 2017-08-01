#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkKey(string input){
    for(int i = 0; i < strlen(input); i++){
        if(!isalpha(input[i])){
            printf("Usage: ./vigenere k\n");
            return false;
        }
    }
    return true;
}

void cipherLetter(char letter, char key){
    if(isupper(key)){
        key -= 65;
    }
    else if(islower(key)){
        key -= 97;
    }
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
}

void getCipher(string input, string key){
    if(strlen(input)>0){
        int j = 0;
        for(int i = 0; i < strlen(input); i++){
            char letter = input[i];
            if(isalpha(letter)){
                cipherLetter(letter, key[j]);
                j++;
                if(j >= (strlen(key)))
                    j = 0;
            }
            else
                printf("%c", letter); 
        }
    }
    printf("\n"); 
}



int main(int argc, string argv[]){
    if(argc == 2){
        string inputInitial = argv[1];
        if(checkKey(inputInitial)){
            printf("plaintext: ");
            string input = get_string();
            printf("ciphertext: ");
            getCipher(input,inputInitial);
            return 0;
        }
    }
    else{
        printf("Usage: ./vigenere k\n");
        return 1;
    }
}