#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *fixed_xor(char *buf1, char *buf2);

int main(void) {
    char *p = fixed_xor("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965");
    printf("%s\n", p);
    // for (int i = 0; p[i] != '\0'; i++) printf("%x", p[i]);
    printf("\n");
    free(p);
    return 0;
}

char *fixed_xor(char *buf1, char *buf2) {
    int length = strlen(buf1);
    if (length != strlen(buf2)) printf("Please enter two equal length buffers");

    unsigned char *hex_int1 = malloc(length / 2);
    unsigned char *hex_int2 = malloc(length / 2);

    unsigned char *xor = malloc(length / 2 + 1);
    xor[length / 2] = '\0';

    unsigned char str_hex_byte1[3] = {[2] = '\0'};
    unsigned char str_hex_byte2[3] = {[2] = '\0'};
    int j = 0;
    for (int i = 0; i < length; i += 2) {
        str_hex_byte1[0] = buf1[i];
        str_hex_byte1[1] = buf1[i+1];

        str_hex_byte2[0] = buf2[i];
        str_hex_byte2[1] = buf2[i+1];
        // printf("\nstr_hex_byte1: %s\n", str_hex_byte1);
        // printf("str_hex_byte2: %s\n", str_hex_byte2);

        hex_int1[j] = strtol(str_hex_byte1, NULL, 16);
        hex_int2[j] = strtol(str_hex_byte2, NULL, 16);
        // printf("hex_int1[%d] = %x\n", j, hex_int1[j]);
        // printf("hex_int2[%d] = %x\n", j, hex_int2[j]);

        j++;
    }
    hex_int1[j] = '\0';
    hex_int2[j] = '\0';

    // printf("hex_int1: %s\n", hex_int1);
    // for (int i = 0; i < length / 2; i++) printf("%x", hex_int1[i]);
    // printf("\n");
    // for (int i = 0; i < length / 2; i++) printf("%x", hex_int2[i]);
    // printf("\n");
    // printf("hex_int2: %s\n", hex_int2);

    unsigned char value;
    for (int k = 0; k < length / 2; k++) {
        xor[k] = hex_int1[k] ^ hex_int2[k];
    }

    free(hex_int1);
    free(hex_int2);
    return xor;
}