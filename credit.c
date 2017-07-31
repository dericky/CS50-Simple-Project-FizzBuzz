#include <stdio.h>
#include <cs50.h>
#include <string.h>

//This script checks inputted strings for validity as credit card numbers
int getLength(long long input){
    int length = 0;
    while(input > 0){
        length++;
        input /= 10;
    }
    return length;
}

string getCardType(long long input, int length){
    if(length == 15){
        long long firstTwo = input / 10000000000000;
        if(firstTwo == 37 || firstTwo == 34)
            return "AMEX\n";
    }
    else if(length == 16){
        long long firstTwo = input / 100000000000000;
        if(firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || firstTwo == 54 || firstTwo == 55)
            return "MASTERCARD\n";
        else{
            firstTwo /= 10;
            if(firstTwo == 4){
                return "VISA\n";
            }
        } 
    }
    else{
        long long firstTwo = input / 1000000000000;
        if(firstTwo == 4){
            return "VISA\n";
        }
    
    }
    return "INVALID";
}


bool checkValidity(long long input){
    if(input < 0)
        return false;
    int length = getLength(input);
    
    if(length == 13 || length == 15 || length == 16){
        int sumOfTimes = 0;
        int sumOthers = 0;
        int sumOfTimes2 = 0;
        long long temp = input;
        long long temp3 = input;
        while(temp != 0){
            long long temp2 = ((temp % 100) / 10);
            temp /= 100;
            sumOfTimes += (temp2 * 2);
            for(int i = (temp2 * 2); i > 0; i/=10){
                sumOfTimes2 += i % 10;
            }
            
        }
        
        // sum of odd place numbers
        while(temp3 > 0){
            long long temp2 = ((temp3 % 100) % 10);
            temp3 /= 100;
            sumOthers += temp2;
        }
        
        if((sumOfTimes2 + sumOthers) % 10 == 0){
            return true;
        }
    }
    return false;
}



int main(void)
{
    printf("Number: ");
    long input = get_long_long();
    if (checkValidity(input)){
        int length = getLength(input);
        string cardType = getCardType(input, length);
        printf("%s", cardType);
    }
    else{
        printf("INVALID\n");
    }
    
    return 0;
}