#include <stdio.h>
#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"

extern int g_6a9b9c; extern int g_9baadc; extern unsigned char g_9baa96;
extern int d2_CurrentWindowId;
extern char* g_1015ea0;

void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl d2_FindResourceByName(char* name);
int __cdecl d2_AddElementToWindow(int, int, int, int);

/* ADDRESS: GOLDTL 0x00593200 */
void __cdecl fcn_00593200(void)
{
	char s1[0x100];
	char s2[0x100];
	char s3[0x100];
	int flag;
	char ch;
	int slot;
	int row;
	int x; int i;

	d2_SetForm(g_6a9b9c, 2);
	io_AppendText((int) 0x6811b0);
	if (g_9baadc == 0x3f) {
		i = 0; do { ch = ((unsigned char*) 0x9baa76)[i]; s1[i++] = ch; } while (ch);
		i = 0; do { ch = ((unsigned char*) 0x9baa76)[i]; s2[i++] = ch; } while (ch);
	} else {
		i = 0; do { ch = ((unsigned char*) 0x9baa76)[i]; s1[i++] = ch; } while (ch);
		i = 0; do { ch = ((unsigned char*) 0x9baa76)[i]; s2[i++] = ch; } while (ch);
	}
	strupr(s1);
	flag = g_9baa96;
	sprintf(s3, (char*) 0x6a2e38, s1);
	slot = d2_FindResourceByName(s3);
	if (slot == -1) {
		slot = d2_FindResourceByName((char*) 0x6a2e24);
	}
	slot = d2_AddElementToWindow(5, 5, slot, d2_CurrentWindowId);
	x = ((D2_CONTROL_TL*) (g_1015ea0))[slot].width + 0xf;
	row = d2_ShowTxt(x, 0x19, s2, d2_CurrentWindowId);
	sprintf(s1, (char*) 0x6a9bb8, *(int*) 0x14b5d34, flag);
	d2_ShowTxt(x, ((D2_CONTROL_TL*) (g_1015ea0))[row].height + 0x1b, s1, d2_CurrentWindowId);
}
