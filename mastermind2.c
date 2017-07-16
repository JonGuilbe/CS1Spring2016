//
// Created by Jonathan on 2/10/2016.
// Program #3 - Mastermind
// Note: I noticed that the grading criteria asks for a minimum of 5 functions, but I'm not really sure what I could split up into a function that would make sense
// The functions that I'm using are pretty simple and straightforward, I don't see much to chop off.
//

#include <stdio.h>
#include <stdlib.h>

int correctCount;
int** guessesArray;


void checkPerm(int slots, int colors, int* permutation, int guesses){ //Checks to see if information is consistent with input (checks black/white pegs)
    int i,j,k;

    for (i = 0; i < guesses; ++i) {
        int correctPositions = guessesArray[i][slots]; //guessesArray[i][slots] is the amount of black pegs for the guess
        int incorrectPositions = guessesArray[i][slots + 1]; //guessesArray[i][slots + 1] is the amount of white pegs for the guess
        int currentCorrect = 0, currentIncorrect = 0;
        int* colorAppearance = calloc((unsigned int)colors, sizeof(int));
        for (k = 0; k < slots; ++k) {
            colorAppearance[permutation[k]]++;
        }

        for (j = 0; j < slots; ++j) { //Checks for black pegs first to ensure that it isn't overcounting
            if(correctPositions < currentCorrect || incorrectPositions < currentIncorrect){
                return;
            }
            else if(colorAppearance[guessesArray[i][j]] != 0 && permutation[j] == guessesArray[i][j]) {
                colorAppearance[guessesArray[i][j]]--;
                currentCorrect++;
            }
        }
        for(j = 0; j < slots; j++){ //Ensures that we're not counting a black peg as both black and white
            if(correctPositions < currentCorrect || incorrectPositions < currentIncorrect){
                return;
            }
            else if(colorAppearance[guessesArray[i][j]] != 0 && permutation[j] != guessesArray[i][j]){
                colorAppearance[guessesArray[i][j]]--;
                currentIncorrect++;
            }
        }
        free(colorAppearance);
        if(correctPositions != currentCorrect || incorrectPositions != currentIncorrect){
            return;
        }
    }
    correctCount++;
    return;
}

void bruteforce(int slots, int currentSlot,int colors, int* permutation, int guesses){ //cycle through each possible permutation

    int i;
    if(slots == currentSlot){
        checkPerm(slots, colors, permutation, guesses);
        return;
    }

    else{
        for (i = 0; i < colors; ++i) {
            permutation[currentSlot] = i;
            bruteforce(slots,currentSlot + 1, colors, permutation, guesses);
        }
    }
    return;
}

int main(){
    int i, cases;
    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {

        correctCount = 0;
        int j,k,slots,colors,guesses;
        scanf("%d%d%d", &slots, &colors, &guesses);
        guessesArray = malloc(sizeof(int*) * guesses);
        int* permutation = malloc(sizeof(int) * slots);

        for (j = 0; j < guesses; ++j) {
            guessesArray[j] = malloc(sizeof(int) * slots + 2); //Takes in not only the slots, but the results as well.
            for (k = 0; k < slots + 2; ++k) {
                scanf("%d", &guessesArray[j][k]);
            }
        }
        bruteforce(slots,0,colors,permutation,guesses);
        printf("%d\n", correctCount);
        for(j = 0; j < guesses; j++){
            free(guessesArray[j]);
        }
        free(guessesArray);
        free(permutation);
    }

    return 0;
}