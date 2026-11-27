#include "client_types.h"
extern char* g_1015ea0;
extern int g_6a4768;
extern int g_77e8a0;
extern int d2_CurrentWindowId;
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];

int __cdecl fcn_005455b0(void);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_LoadForm(int, int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_SetForm(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00545670 */
int __cdecl d2_CreateActionPopupSlot(char* e, short a2, short a3, int a4, int a5)
{
	int a;
	int i;
	int v;

	if ((e[0x78] & 8) == 0) {
		*(int*) (e + 0x74) = 0;
		return 1;
	}
	for (i = 0, a = 0x77e8c4; a < 0x77e984; a += 0xc, i++) {
		if (*(int*) a == -1) {
			goto found_slot;
		}
	}
	goto allocate_slot;
found_slot:
	if (i >= 0x10) {
allocate_slot:
		i = fcn_005455b0();
	}
	if (i == -1) {
		*(int*) (e + 0x74) = 0;
		return 2;
	}
	if (i > g_6a4768) {
		g_6a4768 = i;
	}
	d2_SetForm(g_77e8a0, 0);
	*(int*) (e + 0x74) = (int) &g_77e8c0[i];
	*(int*) ((char*) *(int*) (e + 0x74)) = (int) e;
	*(int*) ((char*) *(int*) (e + 0x74) + 4) = d2_AddElementToWindow(i << 5, 0, a5, d2_CurrentWindowId);
	v = *(int*) ((char*) *(int*) (e + 0x74) + 4);
	((D2_CONTROL_TL*) (g_1015ea0))[v].value_058 = 1;
	*(int*) ((char*) *(int*) (e + 0x74) + 8) = d2_LoadForm(a2, a3, a4);
	fcn_00471d80(*(int*) ((char*) *(int*) (e + 0x74) + 8), 3);
	d2_SetFormVisibility(*(int*) ((char*) *(int*) (e + 0x74) + 8), 0);
	if (*(int*) ((char*) *(int*) (e + 0x74) + 4) == -1) {
		__asm { int 3 }
	}
	if (*(int*) ((char*) *(int*) (e + 0x74) + 8) == -1) {
		__asm { int 3 }
	}
	return 0;
}
