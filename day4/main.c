#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int currentGamePoints(int winningNumbers[], int numberPool[]) {
    int points = 0;
    int i = 0;

    while (winningNumbers[i] != 0) {
        int j = 0;
        while (numberPool[j] != 0) {
            if (winningNumbers[i] == numberPool[j]) {
                if (points == 0) {
                    points = 1;
                } else {
                    points = points * 2;
                }
            }
            j++;
        }

        i++;
    }

    return points;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int winningNumbers[1024];
    int numberPool[1024];
    int gameStart = -1;
    int gamePoints = 0;
    // remove weird memory problem
    memset(winningNumbers, 0, sizeof(winningNumbers));
    memset(numberPool, 0, sizeof(numberPool));

    fp = fopen("./day4/input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i = 0;
    int j = 0;
    int k[1024];
    memset(k, 0, sizeof(k));
    int w = 0;
    int matches = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        k[w] += 1;
        char *game = strtok(line, ":");
        game = strtok(NULL, ":");

        char *token = strtok(game, " ");
        while (token != NULL) {
            if (gameStart == -1) {
                if (strcmp(token, "|") == 0) {
                    gameStart = 1;
                    token = strtok(NULL, " ");
                    continue;
                }
                winningNumbers[i] = atoi(token);
                i++;
            } else if (gameStart == 1) {
                numberPool[j] = atoi(token);
                j++;
            }
            token = strtok(NULL, " ");
        }
        matches = currentGamePoints(winningNumbers, numberPool);
        printf("Game %d: %d\n", w, matches);

        if (matches <= 2) {
            matches = matches;
        } else {
            matches = matches / 2;
        }

        printf("=================================\n");
        for (int l = 0; l < matches; l++) {
            k[w + 1 + l] += k[w];
            printf("k[%d]: %d\n", w + 1 + l, k[w + 1 + l]);
        }
        printf("=================================\n");

        int currentGamePoint = currentGamePoints(winningNumbers, numberPool);
        gamePoints += currentGamePoint;

        // RESET HERE
        gameStart = -1;
        i = 0;
        j = 0;
        w++;
        // reset winningNumbers and numberPool
        memset(winningNumbers, 0, sizeof(winningNumbers));
        memset(numberPool, 0, sizeof(numberPool));
    }

    printf("Total points: %d\n", gamePoints);

    // sum up all in k
    int sum = 0;
    for (int l = 0; l < 1024; l++) {
        sum += k[l];
    }
    printf("Total games: %d\n", sum);

    fclose(fp);

    return 0;
}
