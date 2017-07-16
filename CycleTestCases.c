#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int used[1001][1001];
    used[0][0] = 1;
    srand(time(NULL));
    FILE* file = fopen("Cycle.txt", "r+");
    fprintf(file, "1000 1000");
    int i;
    for (i = 0; i < 1000; i++) {
        int x = 0, y = 0;
        while (used[x][y]) {
            x =  (rand() * 1000);
            y = x;
            while (y == x)
                y =  (rand() * 1001);
        }
        fprintf(file, "%d %d\n", x, y);
        used[x][y] = 1;
    }
    fclose(file);
    return 0;
}