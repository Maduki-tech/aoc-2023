#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *file = fopen("./day2/input.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    char ch;

    do {
        ch = fgetc(file);
        if (ch == '\n') {
            break;
        }
        printf("%c", ch);
    } while (ch != EOF);

    return 0;
}
