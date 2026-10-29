


// SIZE 0x228
typedef struct {
	char pad0[8];
	char name[0x20];
	char pad28[4];
	int x2c;
	int x30;
	char pad34[4];
	char x38[0x10];
	char x48[0xc];
	char pad54[0x38];
	unsigned short flags;
	char pad8e[0x9e];
	int value;
	char x130[0x40];
	char x170[0x30];
	char pad1a0[8];
	char x1a8[0x40];
	char x1e8[0x40];
} Figure;

extern int g_6a23ac;

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
Figure* __cdecl fcn_00403270(int);

Figure* __cdecl fcn_00523710(void* f)
{
	int v;
	char flag;
	Figure* o;

	if (ls_ReadVfsDataChecked(&v, 4, 1, f) == 0) {
		return 0;
	}
	o = fcn_00403270(v);
	if (ls_ReadVfsDataChecked(o->name, 0x20, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&o->x2c, 4, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&o->x30, 4, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&o->flags, 2, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(o->x170, 0x30, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(o->x130, 0x40, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(o->x38, 0x10, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(o->x48, 0xc, 1, f) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&flag, 1, 1, f) == 0) {
		return 0;
	}
	if (flag == 1) {
		o->flags |= 0x20;
	}
	if (ls_ReadVfsDataChecked(&v, 4, 1, f) == 0) {
		return 0;
	}
	if (g_6a23ac >= 0x10013 && ls_ReadVfsDataChecked(o->x1a8, 0x40, 1, f) == 0) {
		return 0;
	}
	if (g_6a23ac >= 0x1005a && ls_ReadVfsDataChecked(o->x1e8, 0x40, 1, f) == 0) {
		return 0;
	}
	o->value = v;
	o->flags &= 0xdffb;
	return o;
}
