//
// Created by Jonathan on 4/10/2016.
// I used the planes program as a base, fixed to work with ints and the travel times.
//

#include <stdio.h>

typedef struct game{
    int start;
    int end;
    int distances[9];
}game;


int contains(game currentGame, int time);
int getMaxGap(game* games, int length);
int getMaxRec(game* games, int length, int* perm, int* used, int k);
int findMaxTime(int* perm, game* games, int length);
int works(int* perm, game* games, int length, int gap);
int getMaxInterval(game* games, int length);

//Global var with the starting location's distances
int baseDistances[9];

int main(){
    int cases, i;
    scanf("%d", &cases);

    for (i = 0; i < cases; ++i) {
        int gameCount;
        scanf("%d", &gameCount);
        int j,k;
        game games[8];
        // Scanning in start and end times for each game.
        for (j = 0; j < gameCount; ++j) {
            scanf("%d",&games[j].start);
            scanf("%d",&games[j].end );
        }
        //Scanning in distance values, taking into consideration that the start point is not a game, but still has distance values
        for (j = 0; j < gameCount+1; ++j) {
            for (k = 0; k < gameCount + 1; ++k) {
                if(j == 0){
                    scanf("%d", &baseDistances[k]);
                }
                else{
                    scanf("%d",&games[j-1].distances[k]);
                }
            }
        }
        printf("%d\n",getMaxGap(games,gameCount));
    }
    return 0;
}

//checks to make sure that the time fits within the start and end of a game
int contains(game currentGame, int time) {
    return currentGame.start <= time && time <= currentGame.end;
}


int getMaxGap(game *games, int length) {

    int i, perm[8], used[8];
    //initialize used array to 0.
    for (i=0; i<length; i++)
        used[i] = 0;

    return getMaxRec(games, length, perm, used, 0);
}


int getMaxRec(game* games, int length, int* perm, int* used, int k) {

    if (k == length){
        return findMaxTime(perm, games, length);
    }

    int best = 0;

    // Permutation algorithm to test all possible cases
    int i;
    for (i=0; i<length; i++) {
        if (!used[i]) {
            used[i] = 1;
            perm[k] = i;
            int tmp = getMaxRec(games, length, perm, used, k+1);

            if (tmp > best)
                best = tmp;

            used[i] = 0;
        }
    }

    return best;
}

// Binary search to find the largest gap in a permutation
int findMaxTime(int* perm, game* games, int length) {


    int high = getMaxInterval(games, length);
    int low = 0, mid;
    int count = 0;

    while (high >= low) {
        mid = (low+high)/2;
        if (works(perm,games,length,mid)){
            low = mid + 1;
            count = mid;
        }

        else
            high = mid - 1;
    }
    return count;
}

// Returns true if gap is permissible for THIS permutation.
int works(int* perm, game* games, int length, int gap) {

    //We start at the first game
    int curtime = games[perm[0]].start;

    //If it takes longer to get there than it does for the game to start, we need to change our starting time.
    if(curtime < baseDistances[perm[0]+1])
        curtime = baseDistances[perm[0]+1];

    int i;

    for (i=1; i<length; i++) {
        // The first value in each game.distances array is the starting base, so we need to skip over that.
        int nexttime = curtime+gap+games[perm[i-1]].distances[perm[i]+1];

        // Fixes a case where start is later than when you arrive.
        if (nexttime < games[perm[i]].start)
            nexttime = games[perm[i]].start;

        if (!contains(games[perm[i]], nexttime)){
            return 0;
        }
        else{
            curtime = nexttime;
        }
    }

    return 1;
}

int getMaxInterval(game* games, int length) {

    int max = games[0].end;
    int i;
    for (i=1; i<length; i++) {
        if (games[i].end > max)
            max = games[i].end;
    }
    return max;
}