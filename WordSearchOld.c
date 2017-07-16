//
// Created by Jonathan Guilbe on 1/23/2016. DO NOT FORGET TO FREE MEMORY!!!!
// Current problems: The binary search is putting \n's where they don't belong which is screwing up the result? Otherwise it seems done...
// It's ignoring test case 1? Something's getting stuck in the buffer, bleh...
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DIRECTIONS = 8; //shhhhhh
const int DX[] = {-1,-1,-1,0,0,1,1,1};
const int DY[] = {-1,0,1,-1,1,-1,0,1};


char** loadDictionary(int* dictionarySize){ //This is OK, confirmed.
    FILE* dictionaryFile = fopen("C:\\Users\\reneg\\ClionProjects\\Fall2016 CSI\\dictionary.txt", "r");
    fscanf(dictionaryFile,"%d", dictionarySize);
    //printf("%d", *dictionarySize);

    char** dictionary = malloc(sizeof(char *) * (*dictionarySize));

    int i;
    for (i = 0; i < (*dictionarySize); i++) {
        dictionary[i] = malloc(sizeof(char) * 20);
        fscanf(dictionaryFile, "%s", dictionary[i]);
    }

    return dictionary;
}

char* binSearch(char* lookingFor,char** dictionary, int wordCount){ //This "should" be fine as well, might need to fix whatever's wrong with the dictionary?

    int min = 0;
    int max = wordCount - 1;
    printf("We're looking for %s \n", lookingFor);
    while(min <= max){
        int mid = (min + max) / 2;
        //printf("Current mid is %s\n", dictionary[mid]);
        if(strcmp(lookingFor, dictionary[mid]) == -1 ){
            max = mid - 1;
        }
        else if(strcmp(lookingFor, dictionary[mid]) == 1){
            min = mid + 1;
        }
        else{
            printf("Wow, I actually found something!");
            return lookingFor;
        }
    }
    return "";
}

int isValid(char** wordSearchField,int rows, int columns, int x, int y){
    if(rows > x && columns - 1 > y && x > -1 && y > -1){
        return 1;
    }
    else
        return 0;
}

void findWordsFromPoint(char** wordSearchField, int rows, int columns, int x, int y, char** dictionary, int wordCount){



    int change = 0;
    while(change < 8){
        int currentX = x, currentY = y;
        //printf("Literally kill.");
        int validValue = isValid(wordSearchField, rows, columns, currentX, currentY);
        char* tempWord = malloc(sizeof(char) * columns); //freed.
        int counter = 0;
        while(validValue == 1){
            //printf("Supreme Edge.");
            tempWord[counter] = wordSearchField[currentX][currentY];
            tempWord[counter + 1] = '\0';
            if(counter >= 4){
                printf("tempWord is %s", tempWord);
                char* result = malloc(sizeof(char) * counter + 1);
                result = binSearch(tempWord,dictionary,wordCount); //Fix the loadDictionary thing and the 2000 number with the actual values.
                //printf("Result is %s", result);
                if(result != "" || result != "\n"){
                    printf("%s", result);
                }
                free(result);
            }
            currentX += DX[change];
            currentY += DY[change];
            validValue = isValid(wordSearchField, rows,columns, currentX, currentY);
            counter++;
        }
        change++;
        free(tempWord);
    }
}

void searchField(char** wordSearchField, int rows, int columns, char** dictionary, int wordCount){ //This can probably be moved to main to prevent a redundant copy of parameter variables
    //printf("Are you even getting here?");
    int i, j;
    for(i = 0; i < rows; i++){
        //printf("K.");
        for (j = 0; j < columns - 1; ++j) {
            //printf("Maybe it's the find function that's kill?");
            findWordsFromPoint(wordSearchField, rows, columns, i, j, dictionary, wordCount);
            //printf("Wat r u doin.\n");
        }
    }
}

int main(){

    int dictionarySize;
    char** dictionary = loadDictionary(&dictionarySize); //freed
    //printf("what.\n");
    //printf("%d\n", dictionarySize);
    //printf("When in doubt, print it out. Dictionary size is %d and just to confirm that it worked, \nfirst word in the dictionary is %s and the last word is %s", dictionarySize, dictionary[0], dictionary[dictionarySize - 1]);
    int runs, i;
    scanf("%d", &runs);

    for (i = 0; i < runs; ++i) {
        int rows, columns;
        //printf("Ok1.");
        scanf("%d", &rows);
        scanf("%d", &columns);
        columns++; // To account for the null terminator.
        //printf("Ok2.");
        char** wordSearchField = malloc(sizeof(char *) * rows); //freed

        int j, k;
        for(j = 0; j < columns; j++){
            wordSearchField[j] = malloc(sizeof(char) * columns); //freed
        }
        //printf("Ok3.");

        for(j = 0; j < rows; j++){
            for (k = 0; k < columns; ++k) {
                char currentInput;
                scanf("%c", &currentInput);
                while(currentInput == ' '){
                    scanf("%c", &currentInput);
                }
                wordSearchField[j][k] = currentInput; //Tested, all input being read correctly.
                //printf("%c", wordSearchField[j][k]);
            }
        }
        //printf("Ok4.");
        puts("");
        printf("Words Found Grid #%d", i + 1);
        puts("");
        searchField(wordSearchField, rows, columns, dictionary, dictionarySize);
        //printf("Ok5.");
        for(j = 0; j < rows; j++){
            free(wordSearchField[j]);
        }
        free(wordSearchField);

    }
    for(i = 0; i < dictionarySize; i++){
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}
