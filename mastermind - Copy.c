//
// Created by Jonathan Guilbe on 2/8/2016
//

#include <stdio.h>
#include <stdlib.h>


int** isValid;
int moves, slots, correctCount;
void printPerm(int slots, int* permutation);

void valid(int* permutation){ //Bruteforce sends the perm here, valid checks that it's fine, and then passes it to printPerm
    int j;
        for (j = 0; j < slots; ++j) {
            if(isValid[permutation[j]][j])
            //printf("This shit's wrong, dawlg.");
            return;
        }

    printPerm(slots, permutation);
    correctCount++;
}

void validSetup(int** gameState,int** isValid, int slots, int move, int correct, int incorrectLocation){

    int i,j,k;
    if(correct == 0 && incorrectLocation == 0){
        for(i = 0; i < slots; i++){
            isValid[gameState[move][i]][i] = 1;
        }
    }
    else if(correct == 0 && incorrectLocation != 0){
        for(i = 0; i < slots; i++){
            //printf("%d %d", gameState[move][i], isValid [gameState[move][i]] [i]);
            isValid [gameState[move][i]] [i] = 1;
        }
    }
}


void printPerm(int slots, int* permutation){ // Prints the array of integers
    int i;
    for (i = 0; i < slots; ++i) {
        //printf("%d", permutation[i]);
    }
    //printf("\n");
}

void bruteforce(int slots, int currentSlot, int* permutation, int* used){ //cycle through each possible permutation

    int i;
    if(slots == currentSlot){
        valid(permutation);
    }

    for (i = 0; i < slots; ++i) {
        if(!used[i]){
            permutation[currentSlot] = i;
            used[i] = 1;
            bruteforce(slots, currentSlot + 1, permutation, used);
            used[i] = 0;
        }
    }

    return;
}

int main(){

    int cases, i;
    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {
        int colors, j, k;
        correctCount = 0;

        scanf("%d", &slots);
        scanf("%d", &colors);
        scanf("%d", &moves);

        isValid = malloc(sizeof(int *) * colors);
        int** gameState = malloc(sizeof(int * ) * moves);
        int** used = malloc(sizeof(int) * slots); // This is supposed to be 2-d since each slot should have its own "used"...so this malloc size of colors
        int* permutation = malloc(sizeof(used));

        for(j = 0; j < slots; j++){
            used[j] = 0;
        }

        for (j = 0; j < colors; ++j) {
            isValid[j] = calloc((unsigned int)slots ,sizeof(int) );
        }

        for (j = 0; j < moves; ++j) {

            gameState[j] = malloc(sizeof(int) * slots);
            for (k = 0; k < slots; ++k) {
                scanf("%d", &gameState[j][k]);
            }
            int correct, incorrectLocation;
            scanf("%d%d", &correct, &incorrectLocation);
            validSetup(gameState,isValid, slots, j, correct, incorrectLocation);
        }







        bruteforce(slots, 0, permutation, used);

        for (j = 0; j < moves; ++j) {
            free(gameState[j]);
        }
        for(j = 0; j < colors; j++){
            free(isValid);
        }

        /*free(used);
        free(permutation);
        free(isValid);
        free(gameState);*/
        printf("%d\n", correctCount);

    }

    return 0;
}

