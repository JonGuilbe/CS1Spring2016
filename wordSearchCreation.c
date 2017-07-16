//
// Created by reneg on 1/30/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    FILE* createThis = fopen("C:\\Users\\reneg\\ClionProjects\\Fall2016 CSI\\createdSearch.txt", "w");
    int width, height;
    printf("Give me a height: ");
    scanf("%d", &height);
    printf("Give me a width: ");
    scanf("%d", &width);

    char** grid = malloc(sizeof(char *) * height);
    int i, j;
    for (i = 0; i < width; ++i) {
        grid[i] = malloc(sizeof(char) * width);
    }
    srand(time(NULL));
    fprintf(createThis, "1\n");
    fprintf(createThis, "%d %d\n", height, width);
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {

            int randomNum =  (rand() % 25) + 97;
            grid[i][j] = (char)randomNum;
            fprintf(createThis, "%c", grid[i][j]);
            //printf("%d ", randomNum);
        }
        fprintf(createThis, "\n");
    }


    return 0;
}
