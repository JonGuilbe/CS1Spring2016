//
// Created by Jonathan Guilbe on 2/19/2016.
// Program 4
//

#include <stdio.h>
#include <stdlib.h>

// Takes in the input outside of main
void setupArmy(int* army, int size){
    int i;
    for (i = 0; i < size; ++i) {
        scanf("%d", &army[i]);
    }
}


void merge(int* army, int low, int mid, int high){

    int i, size = high - low + 1;

    //Temporary space created to store sorted values before putting them back in the original array.
    int *tempArmy = calloc(size, sizeof(int));

    //index1 = where the first half begins. index2 = where the second half begins. indexTemp is where we're at in the tempArray.
    int index1 = low, index2 = mid, indexTemp = 0;

    //Merge the arrays until the indexes cross over to the other half.
    while((index1 < mid) || (index2 <= high)){
        if(index2 > high || (index1 < mid && army[index1] < army[index2])){
            tempArmy[indexTemp] = army[index1];
            index1++;
            indexTemp++;
        }
        else{
            tempArmy[indexTemp] = army[index2];
            index2++;
            indexTemp++;
        }
    }

    //Copy the temporary values back into the array.
    for (i = low; i <= high; ++i) {
        army[i] = tempArmy[i - low];
    }

}

void mergeSort(int* army, int low, int high){
    //Splits the array in half and preforms a mergeSort of the halves.
    if( low < high){
        mergeSort(army, low, (low + high) / 2);
        mergeSort(army,((low + high) / 2) + 1, high);
        merge(army, low, ((low + high) / 2) + 1, high);
    }


}

int getMaxDefeats(int* attackingArmy, int* defendingArmy, int size){
    int i = 0, j = 0, maxDefeats = 0;

    //Sweeps through the arrays until either of the arrays reaches the end, counting how many times a value in defendingArmy can beat a value in attackingArmy.
    //Since the arrays are sorted, it will use a minimum value for each battle to defeat the attackers.
    while(i < size && j < size){
        if(attackingArmy[i] < defendingArmy[j]){
            maxDefeats++;
            i++;
            j++;
        }
        else{
            j++;
        }
    }
    return maxDefeats;
}

int main(){

    int cases, i;

    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {
        int armySize;
        scanf("%d", &armySize);

        int* attackingArmy = malloc(sizeof(int) * armySize);
        int* defendingArmy = malloc(sizeof(int) * armySize);

        setupArmy(attackingArmy, armySize);
        setupArmy(defendingArmy, armySize);

        mergeSort(attackingArmy, 0, armySize - 1);
        mergeSort(defendingArmy, 0, armySize - 1);

        printf("%d\n", getMaxDefeats(attackingArmy, defendingArmy, armySize));

    }

    return 0;
}
