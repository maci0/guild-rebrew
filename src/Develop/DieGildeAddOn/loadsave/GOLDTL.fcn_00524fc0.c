#include <string.h>
#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
void __cdecl gm_AddTime(void*, int, int, int);

typedef struct CUTSCENE_LOAD_SLOT {
	char pad0[0x14];
	int field14;
	char pad18[0xe];
	char pad26[1];
	char pad27[0x9];
	char field30;
	char pad31[3];
	int field34[0x10];
	char field74;
	char pad75[0x7];
	char field7c[0x98];
} CUTSCENE_LOAD_SLOT;

/* Reads the 0x114-byte slot records of the table at g_9a9660 from a save
 * stream. Records written by version 0x1003f and later carry a timestamp;
 * older ones reuse g_7f4c00. */
/* ADDRESS: GOLDTL 0x00524fc0 */
int __cdecl ls_LoadCutscenes(void* fp)
{
	char buf[0x1000];
	CUTSCENE_LOAD_SLOT* p;
	int count;
	int i;
	int k;

	if (!ls_ReadVfsDataChecked(&count, 4, 1, fp)) {
		return 0;
	}
	i = 0;
	if (count <= 0) {
		return 1;
	}
	p = (CUTSCENE_LOAD_SLOT*) cut_Cutscenes;
	for (; i < count; i++, p++) {
		if (!ls_ReadVfsDataChecked(&p->pad0[0], 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->pad0[8], 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field14, 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->pad26[0], 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field30, 1, 1, fp)) {
			return 0;
		}
		if (ls_SaveVersion >= 0x10059) {
			if (!ls_ReadVfsDataChecked(&p->field34[0], 4, 0x10, fp)) {
				return 0;
			}
		} else {
			if (!ls_ReadVfsDataChecked(buf, 0x40, 0x10, fp)) {
				return 0;
			}
			for (k = 0; k < 16; k++) {
				p->field34[k] = ((int*) buf)[k];
			}
		}
		if (!ls_ReadVfsDataChecked(&p->field74, 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field7c[0], 0x98, 1, fp)) {
			return 0;
		}
		if (ls_SaveVersion >= 0x1003f) {
			if (!ls_ReadVfsDataChecked(&p->pad18[0], 0xe, 1, fp)) {
				return 0;
			}
		} else {
			*(pos14_7f4c00*) (&p->pad18[0]) = gm_GameTime;
			gm_AddTime(&p->pad18[0], i + 1, 0, 0);
		}
		if (ls_SaveVersion >= 0x10040) {
			if (!ls_ReadVfsDataChecked(&p->pad0[0xc], 4, 1, fp)) {
				return 0;
			}
		} else {
			*(int*) (&p->pad0[0xc]) = -1;
		}
	}
	return 1;
}
