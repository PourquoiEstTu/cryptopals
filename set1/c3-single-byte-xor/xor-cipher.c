#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../int_hex.h"

#define ASCII_START 32
#define ASCII_END 126
#define ASCII_LOW_INDEX 97
#define ASCII_HIGH_INDEX 64

struct tuple find_key(char *hexString);
int char_freq(char *string);

struct tuple {
    char key;
    char *string;
};

int main(void) {
    // struct tuple t = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    // int p = char_freq("We cooking beef tonight!");
    // int p = char_freq("etaion shrdlu etaion shrdlu");
    // printf("%d\n", p); 
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
        // strcpy(t[k].string);
        // if (score < letter_freq(string)) {
        //     strcpy(high_string, string);
        //     key = guess;       
        // }
    }
    char *high_string = malloc(strlen(hexString));

    return t[0];
}

int char_freq(char *string) {
    // frequencies of characters from a-z, with space (" ") at the end.
    float freq[] = {0.082f, 0.015f, 0.028f, 0.043f, 0.127f, 0.022f, 
                         0.02f, 0.061f, 0.07f, 0.0016f, 0.0077f, 0.04f, 0.024f,
                         0.067f, 0.075f, 0.019f, 0.00095f, 0.06f, 0.063f, 0.091f,
                         0.028f, 0.0098f, 0.024f, 0.0015f, 0.02f, 0.00074f, 0.127f * 2};
    
    int occurrences;
    double expected;
    int chi_squared = 0;
    for (char i = 'a'; i <= 'z'; i++) { 
        occurrences = 0;
        // finds the number of occurrences of character i
        for (int j = 0; j < strlen(string); j++) {
            if (string[j] == i) occurrences++;
        }
        // finds the _expected_ number of occurrences of character i
        expected = 0;
        for (int k = 0; k < strlen(string); k++) {
            expected += k * freq[i - ASCII_LOW_INDEX];
        }
        chi_squared += (occurrences - expected) * (occurrences - expected) / expected;
    }

    int spaces = 0;
    int expected_spaces = 0;
    // finds the number of spaces
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ' ') spaces++;
    }
    // finds expected number of spaces
    for (int j = 0; j < strlen(string); j++) {
        expected_spaces += j * freq[26];
    }
    chi_squared += (spaces - expected_spaces) * (spaces - expected_spaces) / expected_spaces;
    return chi_squared;
}