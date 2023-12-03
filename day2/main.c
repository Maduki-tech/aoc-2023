#include <_ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) { return a > b ? a : b; }

int isValidGame(char *color, int number) {

    if (strcmp(color, "green") == 0 && number > 13) {
        return -1;
    }
    if (strcmp(color, "red") == 0 && number > 12) {
        return -1;
    }
    if (strcmp(color, "blue") == 0 && number > 14) {
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *file = fopen("./day2/input.txt", "r");
    int gameNumber = 1;
    int gameStarted = 0;

    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    char ch;
    char color[6];
    char number[2];
    int numberIndex = 0;
    int colorIndex = 0;
    int result = 0;
    int validGame = 0;
    int resultByPower = 0;
    int maxBlue = 0;
    int maxRed = 0;
    int maxGreen = 0;

    do {
        ch = fgetc(file);
        if (ch != ':' && gameStarted == 0) {
            continue;
        } else {
            gameStarted = 1;
        }
        if (ch == ' ') {
            continue;
        }
        if (isnumber(ch)) {
            number[numberIndex] = ch;
            numberIndex++;
            continue;
        }
        if (isalpha(ch)) {
            color[colorIndex] = ch;
            colorIndex++;
        }

        if (ch == ',' || ch == ';' || ch == '\n') {
            int numberInt = atoi(number);
            if (isValidGame(color, numberInt) == -1) {
                validGame = -1;
            }
            if (strcmp(color, "green") == 0) {
                maxGreen = max(maxGreen, numberInt);
            } else if (strcmp(color, "red") == 0) {
                maxRed = max(maxRed, numberInt);
            } else if (strcmp(color, "blue") == 0) {
                maxBlue = max(maxBlue, numberInt);
            }

            colorIndex = 0;
            numberIndex = 0;
            for (int i = 0; i < 2; i++) {
                number[i] = '\0';
            }

            for (int i = 0; i < 5; i++) {
                color[i] = '\0';
            }

            if (ch == '\n') {
                if (validGame == 0) {
                    result += gameNumber;
                }
                int tempResult = maxBlue * maxRed * maxGreen;
                resultByPower += tempResult;
                gameStarted = 0;
                maxBlue = 0;
                maxRed = 0;
                maxGreen = 0;
                gameNumber++;
                validGame = 0;
            }
        }

        // printf("%c", ch);
    } while (ch != EOF);

    printf("Result: %d\n", result);
    printf("Result by power: %d\n", resultByPower);

    return 0;
}
