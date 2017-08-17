#include <stdio.h>
#include <cs50.h>
#include <string.h>
/* Derick Yan Harvard CS50 Final Project */


void welcomeUser();
void generateFizzBuzz(int n);

int main(){
    welcomeUser();
    int n = 0;
    while(n < 1){
        printf("Please input a positive integer: ");
        n = get_int();
    }
    generateFizzBuzz(n);
    return 0;
}

void welcomeUser(){
    printf("Welcome to the FizzBuzz Application! This program takes in an integer value from a user, and returns the first n outputs of the fizzbuzz game, where n is the value submitted by the user.\n");
}
void generateFizzBuzz(int n){
    printf("FizzBuzz output: ");
    for(int i = 0; i < n; i++){
        if((i + 1) % 3 == 0){
            if((i + 1) % 5 == 0)
                printf("FizzBuzz");
            else
                printf("Fizz");    
        }
        else if((i + 1) % 5 == 0){
            printf("Buzz");
        } 
        else
            printf("%i", i + 1);
        if((i + 1) != n)
            printf(", ");
    }
    printf("\n");
}
