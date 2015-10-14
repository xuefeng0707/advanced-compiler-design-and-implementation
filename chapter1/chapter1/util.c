#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

string String(char *str) {
	int len = strlen(str) + 1;
	string result = checked_malloc(len);
	strcpy_s(result, len, str);
	return result;
}

void *checked_malloc(int len) {
	void *p = malloc(len);
	assert(p);
	return p;
}