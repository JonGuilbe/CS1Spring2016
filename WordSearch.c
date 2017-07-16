//
// Created by Jonathan Guilbe
// 1/30/2016
// Assignment 2
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DIRECTIONS = 8;
const int DX[] = {-1,-1,-1,0,0,1,1,1};
const int DY[] = {-1,0,1,-1,1,-1,0,1};

// I had a hard time getting the dictionary size from loadDictionary, so this function takes care of it nice and easily
int getDictionarySize(){
    FILE* dictionaryFile = fopen("dictionary.txt", "r");
    //FILE* dictionaryFile = fopen("C:\\Users\\reneg\\ClionProjects\\Fall2016 CSI\\dictionary.txt", "r");
    int dictionarySize = 0;
    fscanf(dictionaryFile, "%d", &dictionarySize);
    return dictionarySize;
}

// Puts all the words in the dictionary in a dynamically allocated array
char** loadDictionary(int dictionarySize){ //This is OK, confirmed.
    FILE* dictionaryFile = fopen("dictionary.txt", "r");
    //FILE* dictionaryFile = fopen("C:\\Users\\reneg\\ClionProjects\\Fall2016 CSI\\dictionary.txt", "r");
    char** dictionary = malloc(sizeof(char *) * (dictionarySize));

    int i;
    char tempWord[20];
    for (i = 0; i < (dictionarySize); i++) {
        fscanf(dictionaryFile, "%s", tempWord);
        dictionary[i] = malloc(sizeof(char) * (strlen(tempWord) + 1));
        strcpy(dictionary[i], tempWord);
    }
    return dictionary;
}

// Binary searches through the dictionary, returns an empty string if it wasn't found, and returns the word if it was found.
char* binSearch(char* lookingFor,char** dictionary, int wordCount){
    int min = 0;
    int max = wordCount - 1;
    while(min <= max){
        int mid = (min + max) / 2;
        char* midWord = dictionary[mid];
        if(strcmp(lookingFor, midWord) == -1 ){
            max = mid - 1;
        }
        else if(strcmp(lookingFor, midWord) == 1){
            min = mid + 1;
        }
        else{
            return lookingFor;
        }
    }
    return "";
}

// Checks to see if the x and y are within the grid. columns - 1 accounts for the null terminator.
int isValid(int rows, int columns, int x, int y){
    if(rows > x && columns - 1 > y && x > -1 && y > -1){
        return 1;
    }
    else {
        return 0;
    }
}

// Goes through all 8 directions for a particular character on the grid. Uses isValid to make sure currentX and currentY are within the grid.
void findWordsFromPoint(char** wordSearchField, int rows, int columns, int x, int y, char** dictionary, int wordCount){

    int change = 0;
    while(change < DIRECTIONS){
        int currentX = x, currentY = y;
        int validValue = isValid(rows, columns, currentX, currentY);
        char* tempWord = malloc(sizeof(char) * 20);
        int counter = 1;
        while(validValue == 1){
            tempWord[counter - 1] = wordSearchField[currentX][currentY];
            tempWord[counter] = '\0';
            if(counter >= 4){
                char* result;
                result = binSearch(tempWord,dictionary,wordCount);
                if(result != "" && result != "\n"){
                    printf("%s\n", result);
                }
            }
            currentX += DX[change];
            currentY += DY[change];
            validValue = isValid(rows,columns, currentX, currentY);
            counter++;
            if(counter > 19){
                break;
            }
        }
        change++;
        free(tempWord);
    }
}
//This can probably be moved to main to prevent a redundant copy of parameter variables, but a direct copy/paste didn't work for whatever reason...
void searchField(char** wordSearchField, int rows, int columns, char** dictionary, int wordCount){
    int i, j;
    for(i = 0; i < rows; i++){
        for (j = 0; j < columns - 1; ++j) {
            findWordsFromPoint(wordSearchField, rows, columns, i, j, dictionary, wordCount);
        }
    }
}

int main(){
    int dictionarySize = getDictionarySize();
    char** dictionary = loadDictionary(dictionarySize);
    int runs, i;
    scanf("%d", &runs);

    for (i = 0; i < runs; ++i) {
        int rows, columns;
        scanf("%d", &rows);
        scanf("%d", &columns);
        columns++; // To account for the null terminator.
        char** wordSearchField = malloc(sizeof(char *) * rows);
        int j;

        for(j = 0; j < columns; j++){
            wordSearchField[j] = malloc(sizeof(char) * columns);
        }
        for(j = 0; j < rows; j++){
            scanf("%s", wordSearchField[j]);
        }

        printf("Words Found Grid #%d", i + 1);
        puts("");

        searchField(wordSearchField, rows, columns, dictionary, dictionarySize);

        for(j = 0; j < rows; j++){
            free(wordSearchField[j]);
        }
        free(wordSearchField);
    }

    // Dictionary is needed for all cases, so it is freed last.
    for(i = 0; i < dictionarySize; i++){
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}
