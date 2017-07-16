//
// Created by Jonathan Guilbe on 3/14/2016.
// Program 5
//

#include <stdlib.h>
#include <stdio.h>

//Makes things a little cleaner as I don't have to pass these variables into traverseMaze or isValid.
int rows, columns;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

// # of elements in the dy and dx arrays.
#define DIRECTIONS 4

struct node{
    int x;
    int y;
    struct node * next;
};

struct queue{
    struct node * front;
    struct node * back;
};

void enqueue(struct queue * Queue, struct node * new);
struct node * dequeue(struct queue * Queue);
char ** createMaze(struct queue * Queue);
int traverseMaze(char** maze, struct queue * Queue);
int isValid(int x, int y);
void freeQueue(struct queue * Queue);
void freeMaze(char** maze);
void freeMazeSteps(int** mazeSteps);

int main(){
    int cases, i;
    scanf("%d", &cases);
    for (i = 0; i < cases; ++i) {

        scanf("%d%d", &rows,&columns);
        //puts("scanned correctly!");
        struct queue * Queue = malloc(sizeof(struct queue));
        //puts("queue created!");
        char** maze = createMaze(Queue);
        //puts("maze created!!");
        int answer = traverseMaze(maze,Queue);
        //puts("traversing!");
        freeQueue(Queue);
        //puts("queue freed!");
        freeMaze(maze);
        //puts("maze freed!");
        printf("%d\n", answer);

    }
    return 0;
}

void enqueue(struct queue * Queue, struct node * new){
    //If the queue is not empty, make the old back point to the new back.
    if(Queue->back != NULL){
        Queue->back->next = new;
    }
    //Set the new node as the new back.
    Queue->back = new;
    //If the front is empty, that means that the front and back should be the same as the new node is the only node.
    if(Queue->front == NULL){
        Queue->front = new;
    }
}

struct node * dequeue(struct queue * Queue){
    //If the queue is empty, then there is nothing to dequeue.
    if(Queue->front == NULL)
        return NULL;
    //If the front and the back are the same, the queue is now empty and should be null to allow the while loop in traverseMaze to complete.
    if(Queue->front == Queue->back){
        Queue->front = NULL;
        Queue->back = NULL;
    }
    //If the queue is not empty, then give the current node to free() in traverseMaze and grab the next node and set it as the new front.
    else{
        struct node * temp = Queue->front;
        Queue->front = temp->next;
        return temp;
    }
    return NULL;
}

char ** createMaze(struct queue * Queue){
    //Takes in the input 1 line at a time, and creates a node for where S is, and sets it as the Queue's front and back.
    int i,j;
    //printf("i and j is %d and %d\n", rows, columns);
    char** maze = malloc(sizeof(char *) * rows);
    for (i = 0; i < rows; ++i) {
        maze[i] = malloc(sizeof(char) * columns);
        scanf("%s", maze[i]);
        //printf("%s\n", maze[i]);
        for (j = 0; j < columns; ++j) {
            if(maze[i][j] == 'S'){
                struct node * start = malloc(sizeof(struct node));
                start->x = i;
                start->y = j;
                Queue->front = start;
                Queue->back = start;
            }
        }
    }
    return maze;
}

int traverseMaze(char** maze, struct queue * Queue){
    int i;
    int** mazeSteps = malloc(sizeof(int *) * rows);
    //Keeps a 2D array of the distance from the start point.
    for (i = 0; i < rows; ++i) {
        mazeSteps[i] = calloc(columns,sizeof(int));
    }
    while(Queue != NULL && Queue->front != NULL){
        int x = Queue->front->x, y = Queue->front->y;
        //Setting visited spaces as X means that they will never be queued again.
        maze[x][y] = 'X';
        for (i = 0; i < DIRECTIONS; ++i) {
            if(isValid(x+dx[i], y+dy[i])){
                //Checks to see if we have arrived at our destination, and if so, adds the extra 1 step required to actually reach it.
                if(maze[x + dx[i]][y+dy[i]] == '~'){
                    int answer = mazeSteps[x][y] + 1;
                    freeMazeSteps(mazeSteps);
                    return answer;
                }
                //Checks to ensure that the valid space is neither a wall or a spot that we have already visited.
                else if(maze[x + dx[i]][y+dy[i]] != 'X'){
                    struct node * new = malloc(sizeof(struct node));
                    new->x = x + dx[i];
                    new->y = y + dy[i];
                    enqueue(Queue,new);
                    maze[x+dx[i]][y+dy[i]] = '_';
                    mazeSteps[x+dx[i]][y+dy[i]] = mazeSteps[x][y] + 1;
                }
            }
        }
        free(dequeue(Queue));
    }
    freeMazeSteps(mazeSteps);
    return -1;
}

//Checks to make sure any x and y are within the boundaries
int isValid(int x, int y){
    if(x >= rows || x < 0 || y >= columns || y < 0){
        return 0;
    }
    return 1;
}

void freeQueue(struct queue * Queue){
    while(Queue->front != NULL){
        dequeue(Queue);
    }
}

void freeMaze(char** maze){
    int i;
    for (i = 0; i < rows; ++i) {
        free(maze[i]);
    }
    free(maze);
}

void freeMazeSteps(int** mazeSteps){
    int i;
    for (i = 0; i < rows; ++i) {
        free(mazeSteps[i]);
    }
    free(mazeSteps);
}
