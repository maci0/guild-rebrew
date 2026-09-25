// FUNCTION: GOLDTL 0x462760
// SIZE: 233

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "zlib.h"

extern char* g_1040498;

gzFile __cdecl fcn_0045ee00(const char*, const char*);
void __cdecl fcn_004625f0(gzFile, FILE*);

void __cdecl fcn_00462760(char* file)
{
	char buf[1024];
	char* infile;
	char* outfile;
	FILE* out;
	gzFile in;
	int len = strlen(file);

	strcpy(buf, file);

	if (len > sizeof(".gz") - 1 && strcmp(file + len - (sizeof(".gz") - 1), ".gz") == 0) {
		infile = file;
		outfile = buf;
		outfile[len - 3] = '\0';
	} else {
		outfile = file;
		infile = buf;
		strcat(infile, ".gz");
	}
	in = fcn_0045ee00(infile, "rb");
	if (in == NULL) {
		fprintf(stderr, "%s: can't gzopen %s\n", g_1040498, infile);
		exit(1);
	}
	out = fopen(outfile, "wb");
	if (out == NULL) {
		perror(file);
		exit(1);
	}
	fcn_004625f0(in, out);

	unlink(infile);
}
