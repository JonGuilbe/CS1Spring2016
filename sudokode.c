/*
 * Jonathan Guilbe
 * 1/14/2016
 * Assignment 1
 * sudokode.c
 */

#include <stdio.h>
#define SIZE 9


int checkBox(int field[SIZE][SIZE], int xlowerLimit, int xupperLimit, int ylowerLimit, int yupperLimit){ //Checks to see if there are any repeat numbers in a 3x3 box
    int i;
    int j;
    int frequency[SIZE];

    // Initializes the frequency Array
    for(i = 0; i < SIZE; i++){
        frequency[i] = 0;
    }

    // Marks numbers as seen
    for(i = xlowerLimit; i < xupperLimit; i++){
        for( j = ylowerLimit; j < yupperLimit; j++){
            frequency[field[i][j] - 1]++;
        }
    }

    // Checks that each number was marked only once.
    i = 0;
    while( i < SIZE){
        if(frequency[i] != 1){
            return 0;
        }
        i++;
    }
    return 1;
}

int checkHorizontal(int field[SIZE][SIZE]){
    int i;
    int j;
    int k;
    int frequency[SIZE];

    for (i = 0; i < SIZE; ++i) {
        // Clears the frequency array
        for(k = 0; k < SIZE; k++){
            frequency[k] = 0;
        }

        for (j = 0; j < SIZE; ++j) {
            // Marks the number at i,j as seen, and declares that the solution is wrong if it was already marked.
            // I shouldn't need to check if a number wasn't marked because for a number to not be marked, some other number has to have been repeated.
            frequency[field[i][j] - 1]++;
            if(frequency[field[i][j] - 1] != 1){
                return 0;
            }
        }
    }
    return 1;
}

int checkVertical(int field[SIZE][SIZE]){
    int i;
    int j;
    int k;
    int frequency[SIZE];

    for (i = 0; i < SIZE; ++i) {
        for(k = 0; k < SIZE; k++){
            frequency[k] = 0;
        }

        for (j = 0; j < SIZE; ++j) {
            frequency[field[j][i] - 1]++;
            if(frequency[field[j][i] - 1] != 1){
                return 0;
            }
        }
    }
    return 1;
}

int main(){

    int puzzles;
    scanf("%d", &puzzles);
    int runs;

    for (runs = 0; runs < puzzles; ++runs) {
        int correctSolution = 1; // If this value is never changed, then the solution is correct.

        int field[SIZE][SIZE];
        int i,j,k,l;

        for (i = 0; i < SIZE; ++i) {
            for (j = 0; j < SIZE; ++j) {
                scanf("%1d",&field[i][j]); // Reads in data
            }
        }

        i = 0;
        while(i <= 6 && correctSolution == 1){
            j = i + 3;
            k = 0;
            while(k <= 6 && correctSolution == 1){
                l = k + 3;
                correctSolution = checkBox(field,i,j,k,l);
                k += 3;
            }
            i += 3;
        }

        if(correctSolution == 1){
            // If the solution is still correct to this point, all horizontal lines are checked.
            correctSolution = checkHorizontal(field);
        }

        if(correctSolution == 1){
            // If the solution is still correct to this point, all vertical lines are checked.
            correctSolution = checkVertical(field);
        }

        if(correctSolution == 1){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
