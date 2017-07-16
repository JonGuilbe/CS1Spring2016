//
// Created by Jonathan on 3/2/2016.
// Made to practice coding linked lists and ALL the sorts!

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node * next;
};

struct node * insertToFront(struct node * ptrList, int number);
void printList(struct node * front);
struct node * insertAtBack(struct node * ptrList, int number);
void bubbleSort(int thisIsAnArray[], int length);
void merge(int thisIsAnArray[], int low, int mid, int high);
void mergeSort(int thisIsAnArray[], int low, int high);

int main(){
    struct node * start = malloc(sizeof(struct node));
    start->data = 2;
    start->next = NULL;
    printList(start);
    start = insertToFront(start, 3);
    printList(start);
    start = insertToFront(start, 3);
    printList(start);
    start = insertToFront(start, 4);
    printList(start);
    start = insertToFront(start, 22);
    printList(start);
    start = insertAtBack(start, 22);
    printList(start);
    start = insertAtBack(start, 22);
    printList(start);
    start = insertAtBack(start, 11);
    printList(start);
    start = insertAtBack(start, 12);
    printList(start);
    int array[] = {1,2312414,123,46,134,-12};
    bubbleSort(array, 6);
    int i;
    for (i = 0; i < 6; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");



    return 0;
}

struct node * insertToFront(struct node * ptrList, int number){
    struct node * temp = malloc(sizeof(struct node));

    temp->data = number;
    temp->next = ptrList;

    return temp;
}

struct node * insertAtBack(struct node * ptrList, int number){
    struct node * temp = malloc(sizeof(struct node));
    temp->data = number;
    struct node * current = ptrList;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = temp;
    temp->next = NULL;
    return ptrList;
}


void printList(struct node * front){
    struct node * currentPoint = front;

    while(currentPoint != NULL){
        printf("%d ", currentPoint->data);
        currentPoint = currentPoint->next;
    }
    printf("\n");
}

void bubbleSort(int thisIsAnArray[], int length){
    int i, j;
    for (i = length - 1; i > 0 ; --i) {
        for (j = 0; j < i; ++j) {
            if(thisIsAnArray[j] > thisIsAnArray[j + 1]){
                int temp = thisIsAnArray[j];
                thisIsAnArray[j] = thisIsAnArray[j + 1];
                thisIsAnArray[j + 1] = temp;
            }
        }
    }
}

void mergeSort(int thisIsAnArray[], int low, int high){
    if(low < high){
        mergeSort(thisIsAnArray, low, (low + high) / 2);
        mergeSort(thisIsAnArray, ((low + high) / 2) + 1, high);
        merge(thisIsAnArray,low,  ((low + high) / 2) + 1, high);
    }
}

void merge(int thisIsAnArray[], int low, int mid, int high){

    int size = high - low + 1;
    int* tempArray = malloc(sizeof(int) * size);
    int firstCounter = 0;
    int secondCounter = mid;
    int tempCounter = 0;
    while(firstCounter < mid && secondCounter < high + 1 && tempCounter <= high){
        if(thisIsAnArray[firstCounter] < thisIsAnArray[secondCounter]){
            tempArray[tempCounter] = thisIsAnArray[firstCounter];
            tempCounter++;
            firstCounter++;
        }
        else{
            tempArray[tempCounter] = thisIsAnArray[secondCounter];
            tempCounter++;
            secondCounter++;
        }
    }
    free(tempArray);
}