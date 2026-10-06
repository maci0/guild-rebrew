// FUNCTION: GOLDTL 0x0058c780

typedef struct
{
	char pad0[0x38];
	int x38;
	char pad3c[0x10];
	int x4c;
	char pad50[0x2f4 - 0x50];
} Ctl;
// SIZE 0x2f4

extern char* g_1015ea0;

void __cdecl fcn_00472640(int, int);
int __cdecl gv_CheckSlotActive(void* slot, int type);

int __cdecl fcn_0058c780(char* a1, int a2, int a3, int* a4, int* a5)
{
	int r;
	int sel;
	int i;



	r = 0;
	sel = -1;
	for (i = 0; i < a2 + 1; i++) {
		fcn_00472640(a4[i], 0);
		((Ctl*)g_1015ea0)[a4[i]].x38 = 0;
	}
	for (i = a2 + 1; i < 4; i++) {
		if (gv_CheckSlotActive(*(void**) (a1 + 0x65), i)) {
			r = 1;
			fcn_00472640(a4[i], 1);
			if (sel == -1) {
				sel = i;
			}
		} else {
			fcn_00472640(a4[i], 0);
			((Ctl*)g_1015ea0)[a4[i]].x38 = 0;
		}
	}
	if (((Ctl*)g_1015ea0)[a4[*a5]].x4c != 0 && sel != -1) {
		*a5 = sel;
		((Ctl*)g_1015ea0)[a4[sel]].x38 = 1;
	}
	return r;
}
