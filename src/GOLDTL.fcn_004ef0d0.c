// FUNCTION: GOLDTL 0x004ef0d0
// FUNCTION: GOLD 0x004ed270

#include <stdio.h>

#include "g_68e020.h"

extern Entry68e020 g_68e020[32];
extern char g_68fedc[];
extern char g_68fea0[];

int __cdecl ls_ReadVfsDataChecked(void* p, int size, int n, void* file);

int __cdecl fcn_004ef0d0(void* file)
{
	unsigned char val;
	char fc[5];
	unsigned int n;
	int key;
	char buf[256];
	unsigned int i;
	unsigned int k;

	if (file == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, file)) {
		return 0;
	}
	if (n != 32) {
		sprintf(buf, g_68fedc, 32, n);
	}
	for (k = 0; k < 32; k++) {
		g_68e020[k].state = 0xff;
	}
	for (i = 0; i < n; i++) {
		if (!ls_ReadVfsDataChecked(&key, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&val, 1, 1, file)) {
			return 0;
		}
		for (k = 0; k < 32; k++) {
			if (g_68e020[k].key == key) {
				g_68e020[k].state = val;
				goto next;
			}
		}
		*(int*) &fc[1] = 0;
		fc[3] = (char) key;
		fc[2] = (char) ((unsigned int) key >> 8);
		fc[4] = 0;
		fc[1] = (char) ((unsigned int) key >> 16);
		fc[0] = (char) ((unsigned int) key >> 24);
		sprintf(buf, g_68fea0, fc);
next:;
	}
	for (k = 0; k < 32; k++) {
		if (g_68e020[k].state == 0xff) {
			sprintf(buf, g_68fea0, g_68e020[k].name);
			g_68e020[k].state = 0;
		}
	}
	return 1;
}
