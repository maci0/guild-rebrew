void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int id;
	char pad4[0x20];
} CRIME_SLOT_STUB;
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
} CRIME_RECORD;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} CRIME_PAIR;

#include "Develop/client_types.h"
extern Slot_68ff80 g_68ff80[29];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

/* ADDRESS: GOLDTL 0x004f4c40 */
int __cdecl ls_LoadCrimeRecords(void* f)
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
		if (ls_ReadVfsDataChecked(&((CRIME_SLOT_STUB*)g_68ff80)[i].id, 4, 1, f) == 0)
			return 0;
	}
	if (ls_ReadVfsDataChecked(&cm_LastCrimeId, 4, 1, f) == 0)
		return 0;
	if (ls_SaveVersion >= 0x10041) {
		if (ls_ReadVfsDataChecked(&n1, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&n2, 4, 1, f) == 0)
			return 0;
	}
	for (i = 0; (unsigned int)i < n1; i++) {
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].id, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(((CRIME_RECORD*)cm_CrimeRecords)[i].name, 0xe, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].a, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].b, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].c, 2, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].d, 1, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].e, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].f, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_RECORD*)cm_CrimeRecords)[i].g, 4, 1, f) == 0)
			return 0;
	}
	for (; i < 0x200; i++) {
		((CRIME_RECORD*)cm_CrimeRecords)[i].id = -1;
		((CRIME_RECORD*)cm_CrimeRecords)[i].a = -1;
		((CRIME_RECORD*)cm_CrimeRecords)[i].b = -1;
		((CRIME_RECORD*)cm_CrimeRecords)[i].c = 0;
		((CRIME_RECORD*)cm_CrimeRecords)[i].g = 0;
	}
	memset(((CRIME_PAIR*)cm_CrimeEvidenceLinks), 0xff, 0x800 * sizeof(CRIME_PAIR));
	for (i = 0; (unsigned int)i < n2; i++) {
		if (ls_ReadVfsDataChecked(&((CRIME_PAIR*)cm_CrimeEvidenceLinks)[i].a, 4, 1, f) == 0)
			return 0;
		if (ls_ReadVfsDataChecked(&((CRIME_PAIR*)cm_CrimeEvidenceLinks)[i].b, 4, 1, f) == 0)
			return 0;
	}
	return 1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_99f800[16384];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_9a1800[8192];
#endif
unsigned char _dpad_9a3800[23072];
