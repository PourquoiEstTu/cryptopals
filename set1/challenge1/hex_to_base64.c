#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hex_to_base64.h"

char *hex_to_base64(const char *hexString);

int main(void) {
	char *p = hex_to_base64("4927");
	printf("%s\n", p);
	free(p);
	return 0;
}

char *hex_to_base64(const char *hexString) {
	int length = (int) strlen(hexString);

	// bad input checking
	if (length <= 1) {
		printf("Please enter at least a full byte of data");
		return NULL;
	}
	if (length % 2 != 0) {
		printf("Please enter a hexadecimal string");
		return NULL;
	}

	// all characters in base 64 ordered by index (0-64)
	char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	// will contain the base 64 string
	unsigned char *base64_str = malloc(length * 0.75);
	
	// next 4 lines for converting hex string to hex integer
	char str_hex_byte[3] = {[2] = '\0'};
	unsigned char byte;
	unsigned char mask = (unsigned char) (0xff << 2); // mask = 0b11111100, filters out the first 6 bits
	unsigned char leftover = 0;

	bool swap = true; // makes the loop handle leftover bits
	int j = 0;
	int i = 0;
	while (i < length) {
		if (swap) {
			if (i == length - 1) {
				// case of one hex character left (4 bits left)
				str_hex_byte[0] = hexString[i];
				byte = strtol(str_hex_byte, NULL, 16);
				base64_str[j] = base64[byte << 2];
				i++;
				j++;
				break;
			}
			str_hex_byte[0] = hexString[i];
			str_hex_byte[1] = hexString[i + 1];

			byte = 0;
			byte = strtol(str_hex_byte, NULL, 16); // converts string to integer

			base64_str[j] = base64[byte >> 2]; // index is a group of 6 bits
			leftover = (byte & ~mask); // the two bits cut off from above
			i += 2;
			j++;
			swap = false;
		}
		else {
			str_hex_byte[0] = hexString[i];
			str_hex_byte[1] = '\0';

			byte = 0;
			byte = strtol(str_hex_byte, NULL, 16); // byte = 0000cdef
			
			byte |= (leftover << 4); // byte is now 00abcdef
			base64_str[j] = base64[byte];

			leftover = 0;
			i++;
			j++;
			swap = true;
		}
	}
	base64_str[j] = '\0';
	// char *p = base64_str;
	return base64_str;
}

/* INCOMPLETE - this version will only work only for 64 bit integers */
// char *hex_to_base64(const char *hexString) {
// 	int length = strlen(hexString);

// 	unsigned long long int hex_int = strtol(hexString, NULL, 16);

// 	// bad input checking
// 	if (length <= 1) {
// 		printf("Please enter at least a full byte of data");
// 		return NULL;
// 	}
// 	if (length % 2 != 0) {
// 		printf("Please enter a hexadecimal string");
// 		return NULL;
// 	}

// 	// all characters in base 64 ordered by index (0-64)
// 	char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// 	// will contain the base 64 string
// 	char *base64_str = malloc(length);

// 	unsigned long long int index_mask = 0xfc00000000000000;
// 	unsigned long long int reset_mask = ~index_mask;
// 	int shift = 58;
// 	unsigned int index;

// 	int j = 0;
// 	for (index_mask; index_mask != 0x0f; index_mask >> 6) {
// 		index = (hex_int & index_mask) >> shift;
// 		base64_str[j++] = base64[index];
// 		hex_int &= reset_mask;
// 		shift -= 6;
// 	}
// 	base64_str[j++] = base64[(hex_int & reset_mask) << 2];
// 	base64_str[j] = '\0';
// 	return base64_str;
// }

