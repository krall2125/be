#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct sigmastr {
	char *cstr;
	size_t len;
} sstr_t;

sstr_t from_cstr(char *str) {
	int len = strlen(str);
	sstr_t sigma = (sstr_t) {
		.cstr = malloc(len),
		.len = len
	};

	strcpy(sigma.cstr, str);

	return sigma;
}

sstr_t sclone(sstr_t *str) {
	sstr_t clone = (sstr_t) {
		.cstr = malloc(str->len),
		.len = str->len
	};

	strcpy(clone.cstr, str->cstr);

	return clone;
}

void sfree(sstr_t *str) {
	free(str->cstr);

	str->cstr = NULL;
	str->len = 0;
}
