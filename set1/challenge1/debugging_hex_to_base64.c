#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *hex_to_base64(const char *hexString);

int main(void) {
	//char *a = hex_to_base64("ad");
	char *p = hex_to_base64("2547b5d49a93b57abeb2923352d0a31c989a74fed4ac50a52a7fa72435a003ea");
	// unsigned char *p = byte_cut(0x0d, 2);
	printf("%s\n", p);
	return 0;
}

/* to fix the weird error, make base64_str dynamically allocated like
 * in the non-debugging version of this program */
char *hex_to_base64(const char *hexString) {
	int length = (int) strlen(hexString);

	// printf("length: %d\n", length);
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

	// unsigned char hex[length/2 + 1]; // for printing out base64 string
	unsigned char base64_str[200];
	
	unsigned char str_hex_byte[3] = {[2] = '\0'};
	int base64_indices[2];
	unsigned char byte;
	unsigned char mask = (unsigned char) (0xff << 2);
	unsigned char leftover = 0;
	bool swap = true;

	int j = 0;
	int i = 0;
	while (i < length) {
		if (swap) {
			// printf("\nIter %d without leftover\n", j);

			if (i == length - 1) {
				// printf("\there\n");
				str_hex_byte[0] = hexString[i];
				// printf("str_hex_byte: %s\n", str_hex_byte);
				byte = strtol(str_hex_byte, NULL, 16);
				// printf("byte: %x\n", byte);
				// printf("byte << 2: %x\n", byte << 2);
				base64_str[j] = base64[byte << 2];
				// printf("\tbase64_str[j] = %c\n\n", base64_str[j]);
				i++;
				j++;
				break;
			}

			str_hex_byte[0] = hexString[i];
			str_hex_byte[1] = hexString[i + 1];
			// printf("str_hex_byte: %s\n", str_hex_byte);

			byte = 0;
			byte = strtol(str_hex_byte, NULL, 16);
			// printf("byte: %d\n", byte);

			base64_str[j] = base64[byte >> 2];
			// printf("base64_str[j] = %c\n", base64_str[j]);
			leftover = (byte & ~mask);
			// printf("New leftover: %x\n", leftover);
			i += 2;
			j++;
			swap = false;
		}
		else {
			// printf("\nIter %d with leftover\n", j);
			// if (i == length) {
			// 	base64_str[j] = leftover << 4;
			// 	printf("\there\n");
			// 	printf("\tbase64_str[j] = %c\n", base64_str[j]);
			// 	i++;
			// 	j++;
			// 	break;
			// }

			// printf("hexString: %c\n", hexString[i-1]);
			// printf("i: %d\n", i);
			str_hex_byte[0] = hexString[i];
			str_hex_byte[1] = '\0';
			// printf("\nstr_hex_byte: %c\n", hexString[i]);
			// printf("str_hex_byte: %s\n", str_hex_byte);

			byte = 0;
			byte = strtol(str_hex_byte, NULL, 16);
			
			// printf("byte before mask: %x\n", byte);
			// printf("leftover << 4: %x\n", leftover << 4);
			byte |= (leftover << 4);
			// printf("byte after mask: %x\n", byte);
			base64_str[j] = base64[byte];
			// printf("base64_str[j] = %c\n", base64_str[j]);
			leftover = 0;

			i++;
			j++;
			swap = true;
		}
	}
	base64_str[j] = '\0';
	char *p = base64_str;
	// printf("Size of base64_str: %zu\n", sizeof(base64_str));
	// printf("%s\n", p);
	return p;
}
