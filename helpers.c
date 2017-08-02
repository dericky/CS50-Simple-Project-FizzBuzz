/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool searchHelper(int value, int values[], int first, int last)
{
   if (last >= first)
   {
        int mid = first + (last - first)/2;
        if (value == values[mid])  
            return true;
        if(value < values[mid])
            return searchHelper(value, values, first, mid-1 );
         return searchHelper(value, values, mid+1, last);
   }
    return false;
}

bool search(int value, int values[], int n)
{
    if(searchHelper(value, values, 0, n)){
        return true;
    }
    return false;
}




/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    for(int i = 0; i < n-1; i++){
        int min = i; //smallest value - increments by one each time the loop below executes and selects the next smallest value
        for(int j = i; j < n; j++){
            if(values[min] > values[j]){
                int temp = values[min];
                values[min] = values[j];
                values[j] = temp;
            }
        }
        
    }
}
