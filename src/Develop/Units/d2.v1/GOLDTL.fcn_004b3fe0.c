extern char g_68114c[];
extern char g_681140[];
extern int g_772514;
extern char* g_1015ea0;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;
extern int g_7e46ac;

struct list_4b3fe0 {
	int sel;
	int items[34];
};
// SIZE 0x8c

#include "client_types.h"
extern List8c_102cbc8 g_102cbc8[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl d2_CreateRadioGroup(int);
int* __cdecl fcn_004b3ce0(int, int*);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_004b3ec0(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);


/* ADDRESS: GOLDTL 0x004b3fe0 */
int __cdecl fcn_004b3fe0(int a1)
{
	int result;
	int h;
	int lst;
	int prev;
	int k;
	int* it;
	int* e;

	result = 0xff;
	h = fcn_00470820(0, 0, g_68114c);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190(0x1ace);
	d2_SetForm(h, 2);
	prev = g_772514;
	d2_SetForm(h, 0);
	fcn_0046e830(-1, -1, g_772514, prev, 0x767);
	d2_SetForm(h, 2);
	lst = d2_CreateRadioGroup(0);
	for (it = fcn_004b3ce0(a1, 0); it != 0; it = fcn_004b3ce0(a1, it)) {
		k = fcn_00472250(h, 2, fcn_00519190((int) g_681140, it[2]));
		*(int**) (g_1015ea0 + k * 756 + 0x2f0) = it;
		fcn_00469470(lst, k);
	}
	while (fcn_005373e0(fcn_004b3fe0, 0x1c6) != 0) {
		fcn_00469630(lst);
		if (g_14ce8e0 != 0 || g_14cf950 == 1 || g_100f1dc == 1)
			g_774654 = 1;
		if (g_100f1dc != -1 && ((struct list_4b3fe0*)g_102cbc8)[lst].sel != -1
		    && g_67d370 == ((struct list_4b3fe0*)g_102cbc8)[lst].items[((struct list_4b3fe0*)g_102cbc8)[lst].sel]) {
			e = *(int**) (g_1015ea0 + ((struct list_4b3fe0*)g_102cbc8)[lst].items[((struct list_4b3fe0*)g_102cbc8)[lst].sel] * 756 + 0x2f0);
			if (fcn_004b3ec0(*e, g_7e46ac) != 0) {
				result = *e;
				g_774654 = 1;
			}
		}
	}
	fcn_00469510(lst);
	fcn_00471e30(h);
	return result;
}
unsigned char _dpad_102cbc8[46456];
