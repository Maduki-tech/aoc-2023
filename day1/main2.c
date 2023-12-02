#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wordToDigit(const char *word) {
    // if number in word, return number

    if (strstr(word, "one") != NULL)
        return 1;
    if (strstr(word, "two") != NULL)
        return 2;
    if (strstr(word, "three") != NULL)
        return 3;
    if (strstr(word, "four") != NULL)
        return 4;
    if (strstr(word, "five") != NULL)
        return 5;
    if (strstr(word, "six") != NULL)
        return 6;
    if (strstr(word, "seven") != NULL)
        return 7;
    if (strstr(word, "eight") != NULL)
        return 8;
    if (strstr(word, "nine") != NULL)
        return 9;
    return 0; // Not a digit word
}

void checkDigitWord(char *digitWord, int *firstNumber, int *secondNumber) {
    int digit = wordToDigit(digitWord);
    if (digit != 0) {
        if (*firstNumber == 0) {
            *firstNumber = digit;
        } else {
            *secondNumber = digit;
        }
    }
}

int main(int argc, char *argv[]) {

    FILE *ptr;
    char ch;
    int result = 0;
    int firstNumber = 0;
    int secondNumber = 0;
    char digitWord[6];

    // Opening file in reading mode
    ptr = fopen("./day1/input.txt", "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    // Printing what is written in file
    // character by character using loop.
    int i = 0;
    do {
        ch = fgetc(ptr);

        if (isalpha(ch)) {
            // shift all characters to the left and throw away the first one
            // when digitWord is full
            if (i == 5) {
                for (int j = 0; j < 4; j++) {
                    digitWord[j] = digitWord[j + 1];
                }
                i--;
            }

            digitWord[i] = ch;
            i++;
            checkDigitWord(digitWord, &firstNumber, &secondNumber);
            continue;
        }

        if (isdigit(ch)) {
            if (firstNumber == 0) {
                firstNumber = ch - '0';
            } else {
                secondNumber = ch - '0';
            }

            for (int j = 0; j < sizeof(digitWord); j++) {
                digitWord[j] = '\0';
            }
            i = 0;
            continue;
        }
        if (ch == '\n') {
            if (secondNumber == 0) {
                secondNumber = firstNumber;
            }
            int concat = firstNumber * 10 + secondNumber;
            result += concat;
            firstNumber = 0;
            secondNumber = 0;
            for (int j = 0; j < sizeof(digitWord); j++) {
                digitWord[j] = '\0';
            }
            i = 0;
        }
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);

    printf("result: %d\n", result);

    // Closing the file
    fclose(ptr);
    return 0;
}
