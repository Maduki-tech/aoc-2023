#include <_ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

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
    int firstNumber = 0;
    int secondNumber = 0;
    int numberIndex = 0;
    int colorIndex = 0;
    int result = 0;
    int validGame = 0;

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
            if (firstNumber == 0) {
                firstNumber = ch - '0';
            } else {
                secondNumber = ch - '0';
            }
            continue;
        }
        if (isalpha(ch)) {
            color[colorIndex] = ch;
            colorIndex++;
        }

        if (ch == ',' || ch == ';' || ch == '\n') {
            int concat;
            if (secondNumber == 0) {
                concat = firstNumber;
            } else {
                concat = firstNumber * 10 + secondNumber;
            }
            if (isValidGame(color, concat) == -1) {
                validGame = -1;
            }
            colorIndex = 0;
            numberIndex = 0;

            for (int i = 0; i < 5; i++) {
                color[i] = '\0';
            }
            firstNumber = 0;
            secondNumber = 0;
            if (ch == '\n') {
                printf("validGame: %d\n", validGame);
                if (validGame == 0) {
                    result += gameNumber;
                }
                gameStarted = 0;
                gameNumber++;
            }
        }

        // printf("%c", ch);
    } while (ch != EOF);

    printf("Result: %d\n", result);

    return 0;
}
