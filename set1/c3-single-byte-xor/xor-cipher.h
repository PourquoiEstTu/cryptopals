#ifndef XOR_CIPHER
#define XOR_CIPHER
struct tuple {
	char key;
	char *string;
};
double char_freq(char *string);
struct tuple find_key(char *hexString);
#endif
