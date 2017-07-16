//
// Created by Jonathan Guilbe on 2/8/2016
// Current problem: How the FUCK do I "compare" it with the input to insure that it's "consistent"? This seems like a load of BS...
//

#include <stdio.h>
#include <stdlib.h>


int** isValid;
int moves, slots, correctCount, colors;
void printPerm(int slots, int* permutation);

void valid(int* permutation){ //Bruteforce sends the perm here, valid checks that it's fine, and then passes it to printPerm
    int j;
        for (j = 0; j < slots; ++j) {
            if(isValid[permutation[j]][j]){
            //printPerm(slots, permutation);
            return;}
        }

    //printPerm(slots, permutation);
    correctCount++;
}

void validSetup(int** gameState,int** isValid, int slots, int move, int correct, int incorrectLocation){

    int i,j,k;
    if(correct == 0 && incorrectLocation == 0){
        for(i = 0; i < slots; i++){
            isValid[gameState[move][i]][i] = 1;
            //printf("%d %d\n", gameState[move][i], isValid [gameState[move][i]] [i]);
        }
    }
    else if ((correct + incorrectLocation) == slots){
        int* inSolution = calloc((unsigned int)colors, sizeof(int));
        for(i = 0; i < slots; i++){
            inSolution[gameState[move][i]] = 1;

        }
        for(i = 0; i < colors; i++){
            if(!inSolution[i]){
                for (j = 0; j < slots; j++) {
                    isValid[i][j] = 1;
                    //printf("Summoning Persona!");
                }
            }
        }
    }
    else if(correct == 0 && incorrectLocation != 0){
        for(i = 0; i < slots; i++){

            isValid [gameState[move][i]][i] = 1;

        }
    }

}


void printPerm(int slots, int* permutation){ // Prints the array of integers
    int i;
    for (i = 0; i < slots; ++i) {
        printf("%d", permutation[i]);
    }
    printf(" is not possible.\n");
}

void bruteforce(int slots, int currentSlot,int colors, int* permutation){ //cycle through each possible permutation

    int i, j;
    if(slots == currentSlot){
        valid(permutation);
        return;
    }

    else{
        for (i = 0; i < colors; ++i) {
            permutation[currentSlot] = i;
            bruteforce(slots,currentSlot + 1, colors, permutation);
        }
    }

    return;
}

int main(){

    int cases, i;
    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {
        int j, k;
        correctCount = 0;

        scanf("%d", &slots);
        scanf("%d", &colors);
        scanf("%d", &moves);

        isValid = malloc(sizeof(int *) * colors);
        int** gameState = malloc(sizeof(int * ) * moves);
        int** used = malloc(sizeof(int * ) * slots); // This is supposed to be 2-d since each slot should have its own "used"...so this malloc size of colors
        int* permutation = malloc(sizeof(used));

        for(j = 0; j < slots; j++){
            used[j] = calloc((unsigned int)colors,sizeof(int));
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







        bruteforce(slots, 0,colors, permutation);

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

