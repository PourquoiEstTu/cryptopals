#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char int_to_char(unsigned char i);

int main(void) {
	// char s[] = {126, 125, 120, 75};
	// printf("Is 126 the same as ~?: %s\n", (126 == '~') ? "true" : "false");
	char *string = malloc(16);
	string = "abcdef";
	char *other = malloc(16);
	other = string;
	string[0] = 'z';
	printf("%s\n", string);
	printf("%s\n", other);
	
	/* for (s; s <= 126; s++) {
		printf("%c\n", s);
		printf("%d\n\n", s);
	} */
	return 0;
}
