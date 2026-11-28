

#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char name[0xe];
	int f12;
	int target;
	short count;
	unsigned char kind;
	int f1d;
	int arg;
	int state;
	char pad29[4];
} Order;
#pragma pack()

// SIZE 0x8
#include "Develop/client_types.h"
typedef Pair_99f800 Pair;

// SIZE 0x24
typedef Slot_68ff80 Slot;

extern Slot_68ff80 g_68ff80[29];
extern int cm_LastCrimeId;
extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

int __cdecl vfs_fwrite(void *, int, int, int);

int __cdecl ls_SaveCrimeRecords(int fp)
{
	int n1;
	int n2;
	int ver;
	int i;

	ver = 0x1d;
	n1 = 0;
	n2 = 0;
	if (fp == 0) {
		return 0;
	}
	if (vfs_fwrite(&ver, 4, 1, fp) == 0) {
		return 0;
	}
	for (i = 0; i < 29; i++) {
		if (vfs_fwrite(&g_68ff80[i].v, 4, 1, fp) == 0) {
			return 0;
		}
	}
	if (vfs_fwrite(&cm_LastCrimeId, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (((Order*)cm_CrimeRecords)[i].id != -1) {
			n1++;
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (cm_CrimeEvidenceLinks[i].owner != -1 && cm_CrimeEvidenceLinks[i].key != -1) {
			n2++;
		}
	}
	if (vfs_fwrite(&n1, 4, 1, fp) == -1) {
		return 0;
	}
	if (vfs_fwrite(&n2, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (((Order*)cm_CrimeRecords)[i].id != -1) {
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].id, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(((Order*)cm_CrimeRecords)[i].name, 0xe, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].f12, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].target, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].count, 2, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].kind, 1, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].f1d, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].arg, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)cm_CrimeRecords)[i].state, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (cm_CrimeEvidenceLinks[i].owner != -1 && cm_CrimeEvidenceLinks[i].key != -1) {
			if (vfs_fwrite(&cm_CrimeEvidenceLinks[i].owner, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&cm_CrimeEvidenceLinks[i].key, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	return 1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_99f5e0[544];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_99f5f0[20];
unsigned char _dpad_99f608[24];
unsigned char _dpad_99f688[24];
unsigned char _dpad_99f6a4[60];
unsigned char _dpad_99f6e4[64];
unsigned char _dpad_99f728[64];
unsigned char _dpad_99f76c[64];
unsigned char _dpad_99f7b0[64];
unsigned char _dpad_99f7f4[12];
#endif
