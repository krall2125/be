#include "sigmastr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum bemode {
	M_CMD,
	M_INSERT,
} bmode;

typedef enum cmd {
	CMD_SUBSTITUTE,
	CMD_NONE
} bcmd;

int nextline(char *buffer, int *pos, int *line) {
	if (buffer[*pos] == '\0') return -1;
	while (buffer[*pos] != '\n') {
		(*pos)++;
		if (buffer[*pos] == '\0') return -1;
	}
	(*pos)++;
	if (buffer[*pos] == '\0') return -1;

	(*line)++;

	return 0;
}

int prevline(char *buffer, int *pos, int *line) {
	if (*line == 1) return -1;
	while (buffer[*pos] != '\n') {
		(*pos)--;
	}
	(*pos)--;

	(*line)--;

	return 0;
}

char *getmaballs(sstr_t *str, int line) {
	char *t = strtok(str->cstr, "\n");

	int counter = 1;
	while (t != NULL) {
		if (counter == line) break;
		counter++;
		t = strtok(NULL, "\n");
	}

	return t;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "No filename/more than one filename specified.\n");
		return 1;
	}

	FILE *file = fopen(argv[1], "a+");

	if (file == NULL) {
		fprintf(stderr, "Couldn't open file %s.\n", argv[1]);
		return 1;
	}

	fseek(file, 0L, SEEK_END);

	size_t s = ftell(file);
	rewind(file);

	char *maballs = malloc(s + 1);

	size_t r = fread(maballs, sizeof(char), s, file);
	maballs[r] = '\0';

	int pos = 0;
	int line = 1;

	bmode mode = M_CMD;
	bcmd pending = CMD_NONE;

	while (1) {
		while (pending == CMD_SUBSTITUTE) {
			uint8_t b = 0, b2 = 0;
			uint16_t count = 0;
			scanf("/");
			scanf("%" SCNu8, &b);
			scanf("/");
			scanf("%" SCNu8, &b2);
			scanf("/");
			scanf("%" SCNu16, &count);

			printf("s\\%d\\%d\n", b, b2);
			pending = CMD_NONE;
		}
		if (mode == M_INSERT) {
			uint8_t num = 0;
			scanf("%" SCNu8, &num);
			if (num == 0) {
				printf("MODE :: CMD\n");
				mode = M_CMD;
				continue;
			}

			r += 8;
			char *temp = realloc(maballs, s);
			if (!temp) {
				fprintf(stderr, "Could not write byte to file: memory reallocation error.\n");
				free(maballs);
				fclose(file);
				return 1;
			}

			maballs = temp;

			char ch = num;
			for (int i = pos; i < r; i++) {
				char temp = maballs[i];
				maballs[i] = ch;
				ch = temp;
			}
			continue;
		}

		char c = getc(stdin);

		switch (c) {
		case 'i':
			printf("MODE :: INSERT\n");
			mode = M_INSERT;
			break;
		case 's':
			pending = CMD_SUBSTITUTE;
			break;
		case 'j':
			nextline(maballs, &pos, &line);
			break;
		case 'k':
			prevline(maballs, &pos, &line);
			break;
		case 'p': { // fuck you C23 my cock is a c23 extension
			  // since fucking when can'þ you declare variables in this shit
			  // i have to put fucing block
			sstr_t super_mega_string = from_cstr(maballs);
			char *l = getmaballs(&super_mega_string, line);
			printf("%s\n", l);
			sfree(&super_mega_string);
			break;
		}
		}

		if (c == 'q') break;

		if (c == EOF) break;
	}

	free(maballs);
	fclose(file);
}
