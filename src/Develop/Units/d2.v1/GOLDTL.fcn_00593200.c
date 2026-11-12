#include <stdio.h>
#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"

extern int g_6a9b9c; extern int g_9baadc; extern unsigned char g_9baa96;
extern int g_772514;
extern char* g_1015ea0;

void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl fcn_00465950(char* name);
int __cdecl fcn_0046f740(int, int, int, int);

/* ADDRESS: GOLDTL 0x00593200 */
void __cdecl fcn_00593200(void)
{
	char s1[0x100];
	char s2[0x100];
	char s3[0x100];
	unsigned char c;
	int slot;
	int row;
	int x; int i;

	d2_SetForm(g_6a9b9c, 2);
	io_AppendText((int) 0x6811b0);
	if (g_9baadc == 0x3f) {
		i = 0; do { c = ((unsigned char*) 0x9baa76)[i]; s1[i++] = c; } while (c);
		i = 0; do { c = ((unsigned char*) 0x9baa76)[i]; s2[i++] = c; } while (c);
	} else {
		i = 0; do { c = ((unsigned char*) 0x9baa76)[i]; s1[i++] = c; } while (c);
		i = 0; do { c = ((unsigned char*) 0x9baa76)[i]; s2[i++] = c; } while (c);
	}
	strupr(s1);
	c = g_9baa96;
	sprintf(s3, (char*) 0x6a2e38, s1);
	slot = fcn_00465950(s3);
	if (slot == -1) {
		slot = fcn_00465950((char*) 0x6a2e24);
	}
	slot = fcn_0046f740(5, 5, slot, g_772514);
	x = *(int*) (g_1015ea0 + slot * 0x2f4 + 0x18) + 0xf;
	row = d2_ShowTxt(x, 0x19, s2, g_772514);
	sprintf(s1, (char*) 0x6a9bb8, *(int*) 0x14b5d34, c);
	d2_ShowTxt(x, *(int*) (g_1015ea0 + row * 0x2f4 + 0x1c) + 0x1b, s1, g_772514);
}
