#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../int_hex.h"
#include "xor-cipher.h"

#define ASCII_START 32
#define ASCII_END 126
#define BAD_SCORE 100000000;

// written here for reference
// struct tuple {
//     char key;
//     char *string;
// };

struct tuple find_key(char *hexString);
double char_freq(char *string);

// int main(void) {
//     struct tuple t;
//     t.string = malloc(1000); 
//     t.key = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").key;
//     t.string = find_key("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736").string;
//     printf("t.string: %s\n", t.string);
//     free(t.string);
//     // float p = char_freq("We cooking beef tonight!");
//     // float p = char_freq("Fjjnlkb%HF\"v%iln`%d%ujpka%jc%gdfjk");
//     // float p = char_freq("Hi, how are you?");
//     // printf("%f\n", p); 
//     return 0;
// }

struct tuple find_key(char *hexString) {
    char guess;
    struct tuple ret;
    ret.string = malloc(strlen(hexString));
    double score = BAD_SCORE;

    char *hex_int = int_hex(hexString);

    int j = 0;
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
        // printf("\ncount: %d\n", k);
        // printf("score: %f\n", score);
        // printf("char_freq: %f\n", char_freq(string));
        // printf("%s\n", string);
    }
    free(string);
    free(hex_int);

    return ret;
}

double char_freq(char *string) {
    // frequencies of ascii characters in english text gotten from:
    // https://reusablesec.blogspot.com/2009/05/character-frequency-analysis-info.html

    // const int offset0 = 97;
    // //contains a-z, 97-122 in ascii
    // double alphabet[] = {0.084966, 0.020720, 0.045388, 0.033844, 0.111607, 0.018121, 
    //                     0.024705, 0.030034, 0.075448, 0.001965, 0.011016, 0.054893, 0.030129,
    //                     0.066544, 0.071635, 0.031671, 0.001962, 0.075809, 0.057351, 0.069509,
    //                     0.036308, 0.010074, 0.012899, 0.002903, 0.017779, 0.002722, 0.111607 * (double) 2};

    // const int offset1 = 32;
    //contains ascii chars from 32-47
    // double punct[] = {0.070925 * (double) 2, 0.000306942, 0.00000183067, 0.0000854313, 0.0000970255, 0.0000170863, 0.0000134249, 0.00000122045, 0.00000427156, 0.0000115942, 
    //                     0.000241648, 0.0000231885, 0.0000323418, 0.000197712, 0.000316706,
    //                     0.0000311214};

    // const int offset2 = 48;
    // //contains ascii chars from 48-57
    // double numbers[] = {0.0274381, 0.0435053, 0.0312312, 0.0243339, 0.0194265, 0.0188577, 0.0175647, 
    //                     0.01621, 0.0166225, 0.0179558};

    // const int offset3 = 58;
    // //contains ascii chars from 58-64
    // double punct2[] = {0.00000549201, 0.0000207476, 0.00000427156, 0.0000152556, 0.00000183067, 0.0000207476, 
    //                     0.000238597};

    // const int offset4 = 91;
    // //contains ascii chars from 91-96
    // double punct3[] = {0.000010984, 0.0000115942, 0.000010984, 0.0000195272, 0.000122655, 0.0000115942};

    // const int offset5 = 122;
    // //contains ascii chars from 123-126
    // double punct4[] = {0.00000122045, 0.00000122045,  0.00000610223, 0.0000152556};

    const int offset = 32;
    #define size 69
    // contains ascii chars from 32-126, excluding capital letters
    double freq[size] = {0.111607 * (double) 2, 0.000306942, 0.00000183067, 0.0000854313, 0.0000970255, 
                        0.0000170863, 0.0000134249, 0.00000122045, 0.00000427156, 0.0000115942, 
                        0.000241648, 0.0000231885, 0.0000323418, 0.000197712, 0.000316706,
                        0.0000311214, 0.0274381, 0.0435053, 0.0312312, 0.0243339, 0.0194265, 0.0188577, 0.0175647, 
                        0.01621, 0.0166225, 0.0179558, 0.00000549201, 0.0000207476, 0.00000427156, 0.0000152556, 0.00000183067, 0.0000207476, 
                        0.000238597, 0.000010984, 0.0000115942, 0.000010984, 0.0000195272, 0.000122655, 0.0000115942,
                        0.084966, 0.020720, 0.045388, 0.033844, 0.111607, 0.018121, 
                        0.024705, 0.030034, 0.075448, 0.001965, 0.011016, 0.054893, 0.030129,
                        0.066544, 0.071635, 0.031671, 0.001962, 0.075809, 0.057351, 0.069509,
                        0.036308, 0.010074, 0.012899, 0.002903, 0.017779, 0.002722,
                        0.00000122045, 0.00000122045,  0.00000610223, 0.0000152556};

    int count[size] = {0};
    int length = strlen(string);
    int ignore = 0;

    for (int i = 0; i < length; i++) {
        if (tolower(string[i]) >= offset && tolower(string[i]) <= 122) {
            count[tolower(string[i]) - offset]++;
        }
        // else if (string[i] == ASCII_START) {
        //     count[26]++;
        // }
        // else if (string[i] > ASCII_START && string[i] <= ASCII_END) {
        //     ignore++;
        // }
        else if (string[i] == 9 || string[i] == 10 || string[i] == 13) {
            ignore++;
        }
        else return BAD_SCORE;
    }

    length = length - ignore;
    int occurrences = 0;
    double expected = 0.0;
    double chi_squared = 0.0;
    for (int i = 0; i < size; i++) {
        occurrences = count[i];
        expected = (double) length * freq[i];
        chi_squared += ((double) occurrences - expected) * ((double) occurrences - expected) / expected;
    }
    return chi_squared;
}