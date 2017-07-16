/*
 * Jonathan Guilbe
 * 1/11/2016
 * Program #1: Sudokode
 */

#include "sudokode.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int checkBox(int field[9][9], int xlowerLimit, int xupperLimit, int ylowerLimit,
             int yupperLimit) { //Checks to see if there are any repeat numbers in a 3x3 box
    int i;
    int j;
    int frequency[9];
    int boxIsCorrect = 1;

    for (i = xlowerLimit; i < xupperLimit; i++) {
        for (j = ylowerLimit; j < yupperLimit; j++) {
            frequency[field[i][j]]++;
        }
    }
    i = 0;
    while (i < 9 && boxIsCorrect == 1) {
        if (frequency[i] != 1) {
            return 0;
        }
        i++;
    }
    return 1;
}

int checkNextTo(int **field, int startX,
                int startY) { //Checks all numbers up,down,left and right of a starting point and quits if it encounters a double.
    int boxIsCorrect = 1;
    int changeFactor = 1; //How far we're moving from the start point.
    while (boxIsCorrect == 1 && startX - changeFactor != -1) {  // Checks Values Above the Start Point

        if (field[startX][startY] == field[startX - changeFactor][startY]) {
            return 0;

        }
        changeFactor++;
    }

    changeFactor = 1;

    while (boxIsCorrect == 1 && startX + changeFactor != 9) {  // Checks Values Below the Start Point
        if (field[startX][startY] == field[startX + changeFactor][startY]) {
            boxIsCorrect = 0;
            return 0;


        }
        changeFactor++;
    }

    changeFactor = 1;
    while (boxIsCorrect == 1 && startY - changeFactor != -1) {  // Checks Values To The Left of the Start Point
        if (field[startX][startY] == field[startX][startY - changeFactor]) {
            return 0;

        }
        changeFactor++;
    }

    changeFactor = 1;
    while (boxIsCorrect == 1 && startY + changeFactor != 9) {  // Checks Values To The Right of the Start Point
        if (field[startX][startY] == field[startX][startY + changeFactor]) {
            return 0;

        }
        changeFactor++;
    }

    return 1;
}

int main() {

    int puzzles;
    scanf("%d", &puzzles);
    int runs;

    for (runs = 0; runs < puzzles; ++runs) {
        int correctSolution = 1;

        int field[SIZE][SIZE];
        int i = 0;
        int j = 0;

        for (i = 0; i < SIZE; ++i) {

            for (j = 0; j < SIZE; ++j) {
                scanf("%1d", &field[i][j]);
            }
        }

        i = 0;
        while (i != 1) {
            correctSolution = checkBox(field, 0, 3, 0, 3);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 0, 3, 3, 6);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 0, 3, 6, 9);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 3, 6, 0, 3);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 6, 9, 0, 3);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 3, 6, 3, 6);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 3, 6, 6, 9);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 6, 9, 3, 6);
            if (correctSolution == 0) {
                break;
            }
            correctSolution = checkBox(field, 6, 9, 6, 9);
            if (correctSolution == 0) {
                break;
            }
            i++;
        }

        i = 0;
        j = 0;
        int counter = 0;
        while (i < SIZE && correctSolution == 1) {
            while (j < SIZE && correctSolution == 1) {
                correctSolution = checkNextTo(field, i, j);

                j++;
                counter++;
            }
            i++;
            j = 0;
            counter++;
        }
            printf("What the fuck even.");
        if (correctSolution == 1) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
}

