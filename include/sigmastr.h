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
		.cstr = malloc(len + 1),
		.len = len
	};
	sigma.cstr[len] = '\0';

	strcpy(sigma.cstr, str);

	return sigma;
}

sstr_t sclone(sstr_t *str) {
	sstr_t clone = (sstr_t) {
		.cstr = malloc(str->len),
		.len = str->len
	};
	clone.cstr[str->len - 1] = '\0';

	strcpy(clone.cstr, str->cstr);

	return clone;
}

void sfree(sstr_t *str) {
	free(str->cstr);

	str->cstr = NULL;
	str->len = 0;
}
