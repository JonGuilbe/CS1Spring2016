//
// Created by Jonathan on 3/25/2016.
// Program 6
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//dy and dx arrays make the dfs run without needed 4 for loops
int dx[] = {-1,0,1,1,1,0,-1,-1};
int dy[] = {1,1,1,0,-1,-1,-1,0};
#define DIRECTIONS 8


typedef struct trie{
    int isWord;
    struct trie *nextLetter[26];
}trie;

//Dictionary is stored in a trie, word is set to 1 after the last letter is reached.
//insertInDictionary handles the insertion of the word in the trie
trie * insertInDictionary(trie* dictionary, char *word){
    int length = strlen(word), i,j;
    trie *temp = dictionary;
    for (i = 0; i < length; ++i) {
        if(temp->nextLetter[word[i] - 'a'] == NULL){
            temp->nextLetter[word[i] - 'a'] = malloc(sizeof(trie));
            temp->nextLetter[word[i] - 'a']->isWord = 0;
            for (j = 0; j < 26; ++j) {
                temp->nextLetter[word[i] - 'a']->nextLetter[j] = NULL;
            }
        }
        temp = temp->nextLetter[word[i] - 'a'];
    }
    temp->isWord = 1;
    return dictionary;
}

//fillDictionary handles the opening of the dictionary file and reading in the words, which are then sent to insertInDictionary.
trie * fillDictionary(trie *dictionary){
    FILE* dictionaryFile = fopen("dictionary.txt", "r");
    //FILE* dictionaryFile = fopen("C:\\Users\\reneg\\ClionProjects\\Fall2016 CSI\\dictionary.txt", "r");
    int dictionarySize, i;
    fscanf(dictionaryFile,"%d", &dictionarySize);
    char * currentWord = malloc(sizeof(char*));
    for (i = 0; i < dictionarySize; ++i) {
        fscanf(dictionaryFile,"%s", currentWord);
        insertInDictionary(dictionary, currentWord);
    }
    free(currentWord);
    return dictionary;
}

//checks to see if the word generated from the dfs is an actual word. Returns 1 if it's in the trie and 0 if it isn't.
int isValidWord(trie *dictionary, char* word){
    int length = strlen(word), i,j;
    trie *temp = dictionary;
    for (i = 0; i < length; ++i) {
        if(temp->nextLetter[word[i] - 'a'] == NULL){
            return 0;
        }
        temp = temp->nextLetter[word[i] - 'a'];
    }
    if (temp->isWord)
        return 1;

    return 0;
}

//checks to see if there are any words beyond this point. If no, the dfs should quit and move on.
int isValidPrefix(trie* dictionary, char* word, int length){
    int /*length = strlen(word),*/ i,j;
    trie *temp = dictionary;
    for (i = 0; i < length; ++i) {
        if(temp->nextLetter[word[i] - 'a'] == NULL){
            return 0;
        }
        temp = temp->nextLetter[word[i] - 'a'];
    }
        return 1;
}

//Takes in the boggle board as input
char** getInput(){
    char** board = malloc(sizeof(char**));
    int i;
    for (i = 0; i < 4; ++i) {
        board[i] = malloc(sizeof(char*));
        scanf("%s", board[i]);
    }
    return board;
}

// checks to see if the dfs is about to move to a valid spot
int isValid(int x, int y){
    if(x >= 4 || x < 0 || y >= 4 || y < 0){
        return 0;
    }
    return 1;
}

//runs a dfs to check word combinations. After a combination is 3 characters or longer, it sends it to isValidWord and prints it if that returns 1.
void checkSpot(int x, int y, int **visited, char** board, char *tempWord,trie *dictionary, int counter){

    int  i;
    tempWord[counter - 1] = board[x][y];
    tempWord[counter] = '\0';
    for (i = 0; i < DIRECTIONS; ++i) {
        if(isValid(x+dx[i], y+dy[i]) && !visited[x+dx[i]][y+dy[i]]){
            if(!isValidPrefix(dictionary,tempWord,counter)){
                return;
            }
            if(counter >= 3){
                if(isValidWord(dictionary,tempWord)){
                    printf("%s\n", tempWord);
                }
            }
                visited[x][y] = 1;
                checkSpot(x + dx[i], y + dy[i], visited, board, tempWord, dictionary, counter + 1);
                visited[x][y] = 0;

        }
    }
}

void freeVisited(int** visited){
    int i;
    for (i = 0; i < 4; ++i) {
        free(visited[i]);
    }
    free(visited);
}

void freeBoard(char** board){
    int i;
    for (i = 0; i < 4; ++i) {
        free(board[i]);
    }
    free(board);

}

void freeDictionary(trie* dictionary){
    int i;
    for(i = 0; i < 26; i++){
        if(dictionary->nextLetter[i] != NULL){
            freeDictionary(dictionary->nextLetter[i]);
        }
    }
    free(dictionary);

}

int main(){
    int games, i,j,k;
    scanf("%d", &games);
    trie * dictionary = malloc(sizeof(trie));
    for (j = 0; j < 26; ++j) {
        dictionary->nextLetter[j] = NULL;
    }
    dictionary = fillDictionary(dictionary);
    for (i = 0; i < games; ++i) {


        char** board = getInput();
        int ** visited = malloc(sizeof(int **));
        for (j = 0; j < 4; ++j) {
            visited[j] = calloc(4, sizeof(int *));
        }

        printf("Words for game #%d:\n", i + 1);

        //Uses all 16 spots as a starting point. malloc is * 16 because the max word size is 16.
        char* tempWord = malloc(sizeof(char) * 16);
        for (j = 0; j < 4; ++j) {
            for (k = 0; k < 4; ++k) {
                visited[j][k] = 1;
                checkSpot(j,k,visited,board,tempWord,dictionary,1);
                visited[j][k] = 0;
            }
        }
        free(tempWord);
        free(visited);
        free(board);
        printf("\n\n");
    }
    freeDictionary(dictionary);
    return 0;
}
