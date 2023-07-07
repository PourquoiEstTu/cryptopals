#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "int_hex.h"

char *int_hex(const char *hexString);

/*
int main(void) {

	char *p = int_hex("686974207468652062756c6c277320657965");
	printf("%s\n", p);
	for (int i = 0; i < strlen(p); i++) printf("%x", p[i]);
	printf("\n");
	free(p);
	return 0;
} */

char *int_hex(const char *hexString) {
	int length = (int) strlen(hexString);
	if (length <= 0 || length % 2 != 0) {
		printf("Please enter a valid hexadecimal string");
		return NULL;
	}

	int i;
	if (hexString[0] == '0' && hexString[1] == 'x') i = 2;
	else i = 0;
	
	unsigned char *hex_int = malloc(length);
	unsigned char str_hex_byte[3] = {[2] = '\0'};

	int j = 0;
	for (i; i < length; i += 2) {
		str_hex_byte[0] = hexString[i];
		str_hex_byte[1] = hexString[i+1];
		hex_int[j++] = strtol(str_hex_byte, NULL, 16);
	}
	hex_int[j] = '\0';
	return hex_int;
}
