#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include "zlib.h"

extern char* g_1040498;

void __cdecl fcn_00462500(const char*);
void __cdecl fcn_004625f0(gzFile, FILE*);
void __cdecl fcn_00462530(FILE*, gzFile);
void __cdecl fcn_00462760(char*);
void __cdecl fcn_004626a0(char*, char*);

// FUNCTION: GOLDTL 0x00462850

int __cdecl fcn_00462850(int argc, char* argv[])
{
	int uncompr = 0;
	gzFile file;
	char outmode[20];

	strcpy(outmode, "wb6 ");

	g_1040498 = argv[0];
	argc--, argv++;

	while (argc > 0) {
		if (strcmp(*argv, "-d") == 0)
			uncompr = 1;
		else if (strcmp(*argv, "-f") == 0)
			outmode[3] = 'f';
		else if (strcmp(*argv, "-h") == 0)
			outmode[3] = 'h';
		else if ((*argv)[0] == '-' && (*argv)[1] >= '1' && (*argv)[1] <= '9' && (*argv)[2] == 0)
			outmode[2] = (*argv)[1];
		else
			break;
		argc--, argv++;
	}
	if (argc == 0) {
		setmode(fileno(stdin), O_BINARY);
		setmode(fileno(stdout), O_BINARY);
		if (uncompr) {
			file = gzdopen(fileno(stdin), "rb");
			if (file == NULL)
				fcn_00462500("can't gzdopen stdin");
			fcn_004625f0(file, stdout);
		} else {
			file = gzdopen(fileno(stdout), outmode);
			if (file == NULL)
				fcn_00462500("can't gzdopen stdout");
			fcn_00462530(stdin, file);
		}
	} else {
		do {
			if (uncompr) {
				fcn_00462760(*argv);
			} else {
				fcn_004626a0(*argv, outmode);
			}
		} while (argv++, --argc);
	}
	exit(0);
	return 0;
}
