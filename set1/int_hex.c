#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "int_hex.h"

char *int_hex(const char *hexString);


// int main(void) {

// 	// char *p = int_hex("686974207468652062756c6c277320657965");
// 	unsigned char *p = int_hex("0e3647e8592d35514a081243582536ed3de6734059001e3f535ce6271032");
// 	// printf("%s\n", p);
// 	// printf("p[23]: %x\n", p[22]);
// 	printf("strlen(p) = %d\n", strlen(p));
// 	for (int i = 0; i < strlen(p); i++) printf("%x", p[i]);
// 	printf("\n");
// 	free(p);
// 	return 0;
// } 

char *int_hex(const char *hexString) {
	int length = (int) strlen(hexString);
	if (length <= 0 || length % 2 != 0) {
		printf("Please enter a valid hexadecimal string\n");
		exit(EXIT_FAILURE);
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
		// printf("\nstr_hex_byte[0] = %c\n", str_hex_byte[0]);
		// printf("str_hex_byte[1] = %c\n", str_hex_byte[1]);
		// printf("hex value: %lx\n", strtol(str_hex_byte, NULL, 16));
		hex_int[j++] = strtol(str_hex_byte, NULL, 16);
		// printf("hex_int[j-1] = %x\n", hex_int[j-1]);
	}
	hex_int[j] = '\0';
	for (int i = 0; i < strlen(hex_int); i++) printf("%x", hex_int[i]);
	printf("\n");
	return hex_int;
}
