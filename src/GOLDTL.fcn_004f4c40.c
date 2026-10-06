void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int id;
	char pad4[0x20];
} fcn_004f4c40_Slot;
// SIZE 0x24

#pragma pack(push, 1)
typedef struct
{
	int id;
	char name[0xe];
	int a;
	int b;
	short c;
	char d;
	int e;
	int f;
	int g;
	char pad29[4];
} fcn_004f4c40_Rec;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} fcn_004f4c40_Pair;

#include "client_types.h"
extern Slot_68ff80 g_68ff80[29];
extern int g_773d38;
extern int g_6a23ac;
extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

// FUNCTION: GOLDTL 0x004f4c40
int __cdecl fcn_004f4c40(void* f)
{
	int ver;
	unsigned int n1;
	unsigned int n2;
	int i;

	n1 = 0x80;
	n2 = 0x200;
	if (f == 0)
		return 0;
	if (ls_ReadVfsDataChecked(&ver, 4, 1, f) == 0)
		return 0;
	if (ver != 0x1d)
		return 0;
	for (i = 0; i < 0x1d; i++) {
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Slot*)g_68ff80)[i].id, 4, 1, f) == 0)
			return 0;
	}
	if (ls_ReadVfsDataChecked(&g_773d38, 4, 1, f) == 0)
		return 0;
	if (g_6a23ac >= 0x10041) {
		if (ls_ReadVfsDataChecked(&n1, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&n2, 4, 1, f) == 0)
			return 0;
	}
	for (i = 0; i < n1; i++) {
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].id, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(((fcn_004f4c40_Rec*)g_9a3800)[i].name, 0xe, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].a, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].b, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].c, 2, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].d, 1, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].e, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].f, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Rec*)g_9a3800)[i].g, 4, 1, f) == 0)
			return 0;
	}
	for (; i < 0x200; i++) {
		((fcn_004f4c40_Rec*)g_9a3800)[i].id = -1;
		((fcn_004f4c40_Rec*)g_9a3800)[i].a = -1;
		((fcn_004f4c40_Rec*)g_9a3800)[i].b = -1;
		((fcn_004f4c40_Rec*)g_9a3800)[i].c = 0;
		((fcn_004f4c40_Rec*)g_9a3800)[i].g = 0;
	}
	memset(((fcn_004f4c40_Pair*)g_99f800), 0xff, 0x800 * sizeof(fcn_004f4c40_Pair));
	for (i = 0; i < n2; i++) {
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Pair*)g_99f800)[i].a, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((fcn_004f4c40_Pair*)g_99f800)[i].b, 4, 1, f) == 0)
			return 0;
	}
	return 1;
}
