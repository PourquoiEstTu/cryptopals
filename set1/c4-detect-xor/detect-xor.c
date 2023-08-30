#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../c3-single-byte-xor/xor-cipher.h"
#include "../int_hex.h"

char *detect(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File cannot be opened");
        exit(EXIT_FAILURE);
    } 
    // printf("%d\n", feof(file));
    // printf("%d\n", ferror(file));
    char line[256];
    fgets(line, sizeof(line), file);
    printf("strlen = %d\n", strlen(line));
    unsigned char *hex_line = malloc(256);

    // while (fgets(line, sizeof(line), file)) {
    //     printf("%s\n", line);
    //     printf("%c\n", line[60]);
    //     hex_line = int_hex(line);
    //     // for (int i = 0; i < strlen(hex_line); i++) printf("%x", hex_line[i]);
    //     // printf("\n");
    // }
    free(hex_line);
    fclose(file);
    return "hi";
}
int main(void) {
    detect("4.txt");
    return 0;
}