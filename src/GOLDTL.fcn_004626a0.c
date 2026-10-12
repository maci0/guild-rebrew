// FUNCTION: GOLDTL 0x4626a0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "zlib.h"

extern char* g_1040498;

void __cdecl fcn_00462530(FILE*, gzFile);

void __cdecl fcn_004626a0(char* file, char* mode)
{
	char outfile[1024];
	FILE* in;
	gzFile out;

	strcpy(outfile, file);
	strcat(outfile, ".gz");

	in = fopen(file, "rb");
	if (in == NULL) {
		perror(file);
		exit(1);
	}
	out = gzopen(outfile, mode);
	if (out == NULL) {
		fprintf(stderr, "%s: can't gzopen %s\n", g_1040498, outfile);
		exit(1);
	}
	fcn_00462530(in, out);

	unlink(file);
}
