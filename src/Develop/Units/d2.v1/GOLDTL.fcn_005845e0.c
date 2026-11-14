#include "client_dialog_state.h"
extern int g_14ce8e0, g_100f1dc, g_67d370;
extern char g_14cf950;
extern int g_6a81dc[5];
#include "Develop/Units/d2.v1/d2_gui.h"
char* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(char*);
void __cdecl fcn_00471e30(char*);
int __cdecl fcn_00472250(char*, int, char*);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(char*, int);
char* __cdecl io_AppendText(char*, int);
int __cdecl fcn_005373e0(char*, int);
typedef struct { int i[0x2f4 / 4]; } Row_5845e0;

/* ADDRESS: GOLDTL 0x005845e0 */
int __cdecl fcn_005845e0(void)
{
	char* menu;
	char* item;
	int ids[5];
	char* base;
	int i;
	int k;
	int n;
	int index;
	int result;
	int result2;
	int flag;

	i = 0; flag = 0;
	menu = fcn_00470820(0, 0, (char*) 0x6a9298);
	fcn_00471b60(menu);
	d2_SetForm(menu, 1);
	io_AppendText((char*) 0x6a2f5c, 0x3f1a);
	d2_SetForm(menu, 2);
	for (; i < 5; i++) {
		item = io_AppendText((char*) 0x681140, 0x3f1b + i);
		item = fcn_00472250(menu, 2, item);
		ids[i] = (int) item;
		index = (int) item;
		base = g_1015ea0;
		((Row_5845e0*) g_1015ea0)[index].i[0x58 / 4] = 1;
		((Row_5845e0*) g_1015ea0)[index].i[0x38 / 4] = g_6a81dc[i];
		((Row_5845e0*) g_1015ea0)[index].i[0x1d0 / 4] &= -3;
	}
	item = io_AppendText((char*) 0x681140, 0x3f20);
	result = (int) fcn_00472250(menu, 2, item);
	item = io_AppendText((char*) 0x681140, 0x3f21);
	result2 = (int) fcn_00472250(menu, 2, item);
	d2_SetForm(menu, 2);

	if (fcn_005373e0((char*) 0x5845e0, 0x86) != 0) {
		do {
			base = g_1015ea0;
			n = 0;
			for (k = 0; k < 5; k++) {
				index = ids[k];
				index = index * 0x40 - index;
				index = index * 0xc;
				if (*(int*) (base + index + 0x38) != 0) {
					fcn_00472640((char*) result, 1);
					base = g_1015ea0;
					break;
				}
				n++;
			}
			if (n == 5) {
				fcn_00472640((char*) result, 0);
				base = g_1015ea0;
			}
			if (g_14ce8e0 != 0 || g_14cf950 == 1 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (g_67d370 == result2) {
					g_774654 = 1;
				} else if (g_67d370 == result) {
					g_774654 = 1;
					n = 0;
					for (k = 0; k < 5; k++) {
						index = ids[k];
						index = index * 0x40 - index;
						index = index * 0xc;
						if (*(int*) (base + index + 0x38) != 0) {
							n++;
							g_6a81dc[k] = 1;
						} else {
							g_6a81dc[k] = 0;
						}
					}
					if (n != 0) {
						flag = 1;
					}
				}
			}
		} while (fcn_005373e0((char*) 0x5845e0, 0x86) != 0);
	}
	fcn_00471e30(menu);
	return flag;
}
