#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *ptr;
    char ch;
    int result = 0;
    int firstNumber = 0;
    int secondNumber = 0;
    // Opening file in reading mode
    ptr = fopen("./day1/input.txt", "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    // Printing what is written in file
    // character by character using loop.
    do {
        ch = fgetc(ptr);
        printf("%c", ch);

        if (isdigit(ch)) {
            if (firstNumber == 0) {
                firstNumber = ch - '0';
            } else {
                secondNumber = ch - '0';
            }
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
        }
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);

    printf("result: %d", result);

    // Closing the file
    fclose(ptr);
    return 0;
}
