


#include <stdio.h>
#include <string.h>

#include "rgb.h"

extern Rgb g_100f1a0;
extern int g_773d40;
extern char* g_773d44;
extern char g_1015da0[];
extern char g_696528[];
extern char g_6750e8[];
extern char g_67d940[];

char* __cdecl m_alloc(int size, char* tag);

void __cdecl fcn_00500900(void)
{
	char path[260];
	char line[260];
	FILE* f;

	g_100f1a0.g = 0xff;
	g_100f1a0.r = 0;
	g_100f1a0.b = 0;
	g_773d40 = 0;
	sprintf(path, g_696528, g_1015da0);
	f = fopen(path, g_6750e8);
	if (f != 0) {
		do {
			fread(line, 0x80, 1, f);
			g_773d40++;
		} while (!feof(f));
		fclose(f);
	}
	g_773d44 = m_alloc(g_773d40 * 48, g_67d940);
	g_773d40 = 0;
	f = fopen(path, g_6750e8);
	if (f != 0) {
		do {
			fread(line, 0x80, 1, f);
			strcpy(g_773d44 + g_773d40++ * 48, line);
		} while (!feof(f));
		fclose(f);
	}
}
