// FUNCTION: GOLD 0x004fde90
// SIZE: 283
// FUNCTION: GOLDTL 0x00500900
// SIZE: 283

#include <stdio.h>
#include <string.h>

extern unsigned char g_100f1a0;
extern unsigned char g_100f1a1;
extern unsigned char g_100f1a2;
extern int g_773d40;
extern char* g_773d44;
extern char g_1015da0[];
extern char g_696528[];
extern char g_6750e8[];
extern char g_67d940[];

char* __cdecl fcn_0041db70(int size, char* tag);

void __cdecl fcn_00500900(void)
{
	char path[260];
	char line[260];
	FILE* f;

	g_100f1a1 = 0xff;
	g_100f1a0 = 0;
	g_100f1a2 = 0;
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
	g_773d44 = fcn_0041db70(g_773d40 * 48, g_67d940);
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
