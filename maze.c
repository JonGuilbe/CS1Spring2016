//
// Created by reneg on 3/14/2016.
//
#include <stdlib.h>
#include <stdio.h>

int rows, columns;
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

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
void enqueue(struct queue * Queue, struct node * new);
struct node * dequeue(struct queue * Queue);
char ** createMaze(int rows, int columns, struct queue * Queue);
int traverseMaze(char** maze, struct queue * Queue);
int isValid(int x, int y);



int main(){
    int cases, i;
    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {
        scanf("%d%d", &rows,&columns);
        struct queue * Queue = malloc(sizeof(struct queue));
        char** maze = createMaze(rows, columns, Queue);
        int answer = traverseMaze(maze,Queue);
        printf("%d\n", answer);
        int wtf = ((431-225) - ((225-(431-225))*10)) - (((225 - (431-225)) - ((431-225) - (225 - (431-225))* 10) )) * 5;
    }
    return 0;
}

void enqueue(struct queue * Queue, struct node * new){
    if(Queue->back != NULL){
        Queue->back->next = new;
    }
    Queue->back = new;
    if(Queue->front == NULL){
        Queue->front = new;
    }
    puts("Enqueue is okay.");
}

struct node * dequeue(struct queue * Queue){ //might need to re-do this somehow?
    if(Queue->front == NULL)
        return NULL;
    if(Queue->front == Queue->back){
        Queue->front = NULL;
        Queue->back = NULL;
    }
    else{
        struct node * temp = Queue->front;
        Queue->front = temp->next;
        return temp;}

    puts("Dequeue is okay.");
     //remember to free this later!
    return NULL;
}

char ** createMaze(int rows, int columns, struct queue * Queue){
    int i,j;
    char** maze = malloc(sizeof(char *) * rows);
    for (i = 0; i < rows; ++i) {
        maze[i] = malloc(sizeof(char) * columns);
        scanf("%s", maze[i]);
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
    puts("Maze created!.");
    return maze;
}

int traverseMaze(char** maze, struct queue * Queue){
    int steps = 0;
    while(Queue != NULL && Queue->front != NULL){
        puts("New traversal!");
        steps++;
        int x = Queue->front->x, y = Queue->front->y;
        puts("Alive1");
        int i;
        maze[x][y] = '_';
        puts("Alive2");
        for (i = 0; i < DIRECTIONS; ++i) {
            if(isValid(x+dx[i], y+dy[i])){
                if(maze[x + dx[i]][y+dy[i]] == '~'){
                    return steps;
                }
                else if(maze[x + dx[i]][y+dy[i]] != 'X' && maze[x + dx[i]][y+dy[i]] != '_'){
                    struct node * new = malloc(sizeof(struct node));
                    new->x = x + dx[i];
                    new->y = y + dy[i];
                    enqueue(Queue,new);
                    maze[x+dx[i]][y+dy[i]] = '_';
                }
                else{
                    puts("We're not going here...");
                }
            }
        }

        free(dequeue(Queue));
    }
    return -1;
}

int isValid(int x, int y){
    if(x >= rows || x < 0 || y >= columns || y < 0){
        puts("Invalid number!.");
        return 0;
    }
    puts("Valid number!.");
    return 1;
}


