#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../int_hex.h"

#define ASCII_START
#define ASCII_END 126

struct tuple find_key(char *hexString);
int letter_freq(char *string);

struct tuple {
    char key;
    char *string;
};

int main(void) {
    struct tuple t = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    printf("%s\n", t.string);
    printf("%c\n", t.key);
    return 0;
}

struct tuple find_key(char *hexString) {
    char guess = ' ';
    struct tuple t[ASCII_END - ASCII_START];

    char *hex_int = int_hex(hexString);

    int j;
    int k = 0;
    char *string = malloc(strlen(hexString));
    for (guess; guess <= ASCII_END; guess++) {
        for (j = 0; j < strlen(hex_int); j++) {
            string[j] = hex_int[j] ^ guess;
        }
        // printf("%s\n", string);
        string[++j] = '\0';
        strcpy(t[k].string);
        // if (score < letter_freq(string)) {
        //     strcpy(high_string, string);
        //     key = guess;       
        // }
    }
    char *high_string = malloc(strlen(hexString));

    return ret;
}

int letter_freq(char *string) {
    // int score = 0;
    // char common[] = "etaion shrdlu";
    // for (int i = 0; i < strlen(string); i++) {
    //     for (int j = 0; j < strlen(common); j++) {
    //         if (tolower(string[i]) == common[j]) score++;
    //     }
    // }
    float frequency[] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 
                         0.02, 0.061, 0.07, 0.0016, 0.0077, 0.04, 0.024,
                         0.067, 0.075, 0.019, 0.00095, 0.06, 0.063, 0.091,
                         0.028, 0.0098, 0.024, 0.0015, 0.02, 0.00074, 0.127 * 2}
    return 5;
}