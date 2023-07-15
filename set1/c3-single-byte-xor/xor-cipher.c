#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../int_hex.h"

#define ASCII_START 32
#define ASCII_END 126
#define BAD_SCORE 10000000;

struct tuple find_key(char *hexString);
float char_freq(char *string);

struct tuple {
    char key;
    char *string;
};

int main(void) {
    struct tuple t;
    t.string = malloc(1000); 
    t.key = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").key;
    t.string = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").string;
    printf("t.string: %s\n", t.string);
    free(t.string);
    // int p = char_freq("We cooking beef tonight!");
    // int p = char_freq("etaion shrdlu etaion shrdlu");
    // printf("%f\n", p); 
    return 0;
}

struct tuple find_key(char *hexString) {
    char guess;
    struct tuple ret;
    ret.string = malloc(strlen(hexString));
    float score = 1000000000;

    char *hex_int = int_hex(hexString);

    int j;
    int k = 0;
    char *string = malloc(strlen(hexString));
    for (guess = ASCII_START; guess <= ASCII_END; guess++) {
        k++;
        for (j = 0; j < strlen(hex_int); j++) {
            string[j] = hex_int[j] ^ guess;
        }
        string[++j] = '\0';
        if (score > char_freq(string)) {
            strcpy(ret.string, string);
            ret.key = guess;       
            score = char_freq(string);
        }
        printf("\ncount: %d\n", k);
        printf("score: %f\n", score);
        printf("char_freq: %f\n", char_freq(string));
        printf("%s\n", string);
    }

    return ret;
}

float char_freq(char *string) {
    // frequencies of ascii characters in english text gotten from:
    // https://reusablesec.blogspot.com/2009/05/character-frequency-analysis-info.html

    const int offset0 = 97;
    //contains a-z, 97-122 in ascii
    double freq[] = {0.0752766, 0.0229145, 0.0257276, 0.0276401, 0.070925, 0.012476, 
                         0.0185331, 0.0241319, 0.0469732, 0.00836677, 0.0196828, 0.0377728, 0.0299913,
                         0.0456899, 0.0517, 0.0245578, 0.00346119, 0.0496032, 0.0461079, 0.0387388,
                         0.0210191, 0.00833626, 0.0124492, 0.00573305, 0.0152483, 0.00632558};

    const int offset1 = 32;
    //contains ascii chars from 32-47
    double punct[] = {0.070925 * (double) 2, 0.000306942, 0.00000183067, 0.0000854313, 0.0000970255, 
                        0.0000170863, 0.0000134249, 0.00000122045, 0.00000427156, 0.0000115942, 
                        0.000241648, 0.0000231885, 0.0000323418, 0.000197712, 0.000316706,
                        0.0000311214};

    const int offset2 = 48;
    //contains ascii chars from 48-57
    double numbers[] = {0.0274381, 0.0435053, 0.0312312, 0.0243339, 0.0194265, 0.0188577, 0.0175647, 
                        0.01621, 0.0166225, 0.0179558};

    const int offset3 = 58;
    //contains ascii chars from 58-64
    double punct2[] = {0.00000549201, 0.0000207476, 0.00000427156, 0.0000152556, 0.00000183067, 0.0000207476, 
                        0.000238597};

    const int offset4 = 91;
    //contains ascii chars from 91-96
    double punct3[] = {0.000010984, 0.0000115942, 0.000010984, 0.0000195272, 0.000122655, 0.0000115942};

    const int offset5 = 122;
    //contains ascii chars from 123-126
    double punct4[] = {0.00000122045, 0.00000122045,  0.00000610223, 0.0000152556};

    int count[127-30] = {0};
    int length = strlen(string);
    int ignore = 0;

    for (int i = 0; i < length; i++) {
        if (tolower(string[i]) >= offset0 && tolower(string[i]) <= 122) {
            count[tolower(string[i]) - offset0]++;
            // printf("string[i] - ASCII_LOW_INDEX = %d\n", string[i] - ASCII_LOW_INDEX);
        }
        else if (string[i] == ASCII_START) {
            count[26]++;
        }
        else if (string[i] > ASCII_START && string[i] <= ASCII_END) {
            ignore++;
        }
        else if (string[i] == 9 || string[i] == 10 || string[i] == 13) {
            ignore++;
        }
        else return BAD_SCORE;
    }
    // for (char i = 'a'; i <= 'z'; i++) { 
    //     occurrences = 0;
    //     // finds the number of occurrences of character i
    //     for (int j = 0; j < length; j++) {
    //         if (string[j] == i) occurrences++;
    //     }
    //     // finds the _expected_ number of occurrences of character i
    //     expected = freq[i - ASCII_LOW_INDEX] * (float) length;
    //     // for (int k = 0; k < strlen(string); k++) {
    //     //     expected += k * freq[i - ASCII_LOW_INDEX];
    //     // }
    //     chi_squared += (occurrences - expected) * (occurrences - expected) / expected;
    // }

    // float spaces = 0;
    // float expected_spaces = 0;
    // // finds the number of spaces
    // for (int i = 0; i < strlen(string); i++) {
    //     if (string[i] == ' ') spaces++;
    // }
    // expected_spaces = freq[26] * (float) length;
    // // finds expected number of spaces
    // // for (int j = 0; j < strlen(string); j++) {
    // //     expected_spaces += j * freq[26];
    // // }
    // chi_squared += (spaces - expected_spaces) * (spaces - expected_spaces) / expected_spaces;

    length = length - ignore;
    int occurrences = 0;
    double expected = 0.0;
    double chi_squared = 0.0;
    for (int i = 0; i < 27; i++) {
        occurrences = count[i];
        expected = (float) length * freq[i];
        chi_squared += ((float) occurrences * expected) * ((float) occurrences * expected) / expected;
    }
    return chi_squared;
}