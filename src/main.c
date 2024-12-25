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

char *addressma(const char *str, int line) {
	int linec = 1;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') linec++;
		if (linec == line) {
			return (char *) &str[i];
		}
	}

	return NULL;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "No filename/more than one filename specified.\n");
		return 1;
	}

	// this can be just reading
	FILE *file = fopen(argv[1], "r");

	char *maballs = malloc(1);
	size_t r = 1, s = 1;
	if (file != NULL) {
		fseek(file, 0L, SEEK_END);

		s = ftell(file);
		rewind(file);

		maballs = realloc(maballs, s + 1);

		r = fread(maballs, sizeof(char), s, file);
		maballs[r] = '\0';

		// probbaly can close it here
		fclose(file);
	}
	else {
		fprintf(stderr, "Couldn't open file %s. Proceeding anyway.\n", argv[1]);
	}

	int pos = 0;
	int line = 1;

	bmode mode = M_CMD;
	bcmd pending = CMD_NONE;

	while (1) {
		while (pending == CMD_SUBSTITUTE) {
			uint8_t b = 0, b2 = 0;
			uint16_t count = 1, start = 0;
			scanf("/");
			scanf("%" SCNu8, &b);
			scanf("/");
			scanf("%" SCNu8, &b2);
			scanf("/");
			scanf("%" SCNu16, &count);
			scanf("/");
			scanf("%" SCNu16, &start);

			int replaced = 0;

			char *pch = addressma(maballs, line);
			int pos = 0;

			for (; pch[pos] != '\n' && pch[pos] != '\0'; pos++);

			for (int i = 0; i < start; i++) {
				pch = strchr(pch, b);
				if (pch == NULL) {
					break;
				}
				pch++;
			}

			if (pch == NULL) {
				pending = CMD_NONE;
				break;
			}

			for (int i = 0; i < count; i++) {
				*pch = b2;

				pch = strchr(++pch, b);
				if (pch == NULL) {
					break;
				}
			}

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

			// probably dumb to make the string 8 bytes larger for every byte you want to insert
			if (pos >= r) {
				r += 8;
				char *temp = realloc(maballs, s);
				if (!temp) {
					fprintf(stderr, "Could not write byte to file: memory reallocation error.\n");
					free(maballs);
					return 1;
				}

				maballs = temp;
			}

			if (num == 10) line++;

			char ch = num;
			for (int i = pos; i < r; i++) {
				char temp = maballs[i];
				maballs[i] = ch;
				ch = temp;
			}

			pos++;
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
		case 'p': {
			sstr_t super_mega_string = from_cstr(maballs);
			char *l = getmaballs(&super_mega_string, line);
			printf("%s\n", l);
			sfree(&super_mega_string);
			break;
		}
		case 'w':
			file = fopen(argv[1], "w");
			if (file == NULL) {
				printf("Couldn't open file for whatever reason.\n");
			}
			fprintf(file, "%s", maballs);
			fclose(file);
			break;
		case 'a': {
			int result = nextline(maballs, &pos, &line);
			if (result == 0) line--;
			printf("MODE :: INSERT\n");
			mode = M_INSERT;
			break;
		}
		}

		if (c == 'q') break;

		if (c == EOF) break;
	}

	free(maballs);
}
