#include <stdio.h>
#include <stdlib.h>

int checkBox(int field[9][9], int xlowerLimit, int xupperLimit, int ylowerLimit, int yupperLimit){ //Checks to see if there are any repeat numbers in a 3x3 box
    int i;
    int j;
    int frequency[9];

    for(i = 0; i < 9; i++){
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
    while( i < 9){
        if(frequency[i] != 1){
            return 0;
        }
        i++;
    }
    return 1;
}

/*int checkAround(int **field, int startX, int startY){ //Checks all numbers up,down,left and right of a starting point and quits if it encounters a repeat. Would definitely be a lot faster to only check the boundaries and not every single point.
    int changeFactor = 1; //How far we're moving from the start point.
    while(startX - changeFactor != -1){  // Checks Values Above the Start Point
        if(field[startX][startY] == field[startX - changeFactor][startY]){
            return 0;
        }
        changeFactor++;
    }

    changeFactor = 1;
    while(startX + changeFactor != 9){  // Checks Values Below the Start Point
        if(field[startX][startY] == field[startX + changeFactor][startY]){
            return 0;
        }
        changeFactor++;
    }

    changeFactor = 1;
    while(startY - changeFactor  != -1){  // Checks Values To The Left of the Start Point
        if(field[startX][startY] == field[startX][startY - changeFactor]){
            return 0;
        }
        changeFactor++;
    }

    changeFactor = 1;
    while(startY + changeFactor != 9){  // Checks Values To The Right of the Start Point
        if(field[startX][startY] == field[startX][startY + changeFactor]){
            return 0;
        }
        changeFactor++;
    }
    return 1;
} */

int checkHorizontal(int field[9][9]){
    int i;
    int j;
    int k;
    int frequency[9];

    for (i = 0; i < 9; ++i) {
        for(k = 0; k < 9; k++){
            frequency[k] = 0;
        }

        for (j = 0; j < 9; ++j) {
            frequency[field[i][j] - 1]++;
            if(frequency[field[i][j] - 1] != 1){
                return 0;
            }
        }
    }
    return 1;
}

int checkVertical(int field[9][9]){
    int i;
    int j;
    int k = 0;
    int frequency[9];

    for (i = 0; i < 9; ++i) {
        for(k = 0; k < 9; k++){
            frequency[k] = 0;
        }

        for (j = 0; j < 9; ++j) {
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
        int correctSolution = 1;

        int field[9][9];
        int i = 0;
        int j = 0;

        for (i = 0; i < 9; ++i) {

            for (j = 0; j < 9; ++j) {
                scanf("%1d",&field[i][j]);
            }
        }

        i = 0;
        while( i != 1){
            correctSolution = checkBox(field, 0, 3, 0 , 3);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 0, 3, 3, 6);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 0, 3, 6, 9);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 3, 6, 0, 3);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 6, 9, 0 ,3);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 3, 6, 3, 6);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 3, 6 , 6, 9);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 6, 9,  3, 6);
            if(correctSolution == 0){
                break;
            }
            correctSolution = checkBox(field, 6, 9 , 6, 9);
            if(correctSolution == 0){
                break;
            }
            i++;
        }

        /*
        i = 0;
        j = 0;
        int counter = 0;
        while(i < 9 &&  correctSolution == 1){
            while(j < 9 && correctSolution == 1){
                correctSolution = checkAround(field, i, j);
                j++;
                counter++;
            }
            i++;
            j = 0;
            counter++;
        } */

        if(correctSolution == 1){
            correctSolution = checkHorizontal(field);
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

