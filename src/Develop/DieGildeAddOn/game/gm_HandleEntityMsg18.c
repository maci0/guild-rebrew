#include <string.h>

extern unsigned char gm_ActiveTownIndex; extern double dbl_2_0; extern double dbl_0_01; extern void* __cdecl gm_LookupEntityRecordById(unsigned int);
extern int __cdecl gm_HasActiveSpecialObject(void*, int);
extern void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl gm_FindNextFilteredEntity(void);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
extern int __cdecl io_FormatTextBuffer(char*, int, int);
extern void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
extern void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);
extern void __cdecl cm_RequestCopyEntityData(int, int, int, int);

/* Collects the entity ids in the given building's filter chain, drops repeated
 * ids, emits the remaining ones and announces the building's road segment. */
/* ADDRESS: GOLDTL 0x004b7f70 */
/* ADDRESS: GOLDDE 0x004a6020 */
int __cdecl gm_HandleEntityMsg18(unsigned int* request)
{
	unsigned short* ent;
	int r;
	int ids[16];
	char buf[0x400];
	int cnt;
	int i;
	int m;
	int id;
	int n;
	int v;
	double d;

	cnt = 0;
	ent = (unsigned short*) gm_LookupEntityRecordById(*request);
	if (ent == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(ent, 0x290) != 0) {
		return 0x400;
	}
	n = (int) gm_StartFilteredEntitySearch(1, 5, 7);
	if (n != 0) {
		do {
			if (cnt >= 0x10) {
				break;
			}
			if (*(unsigned short*) ((char*) n + 0x27) != 0xffff) {
				ids[cnt] = *(int*) ((*(unsigned short*) ((char*) n + 0x27) & 0xffff) * 0x21c + 0x7f4ca4);
				cnt += 1;
			}
			n = (int) gm_FindNextFilteredEntity();
		} while (n != 0);
	}
	if (cnt == 0) {
		return 0x400;
	}
	for (i = 0; i < cnt - 1; i++) {
		for (m = i + 1; m < cnt; m++) {
			if (ids[i] == ids[m]) {
				ids[m] = -1;
			}
		}
	}
	for (i = 0; i < cnt; i++) {
		id = ids[i];
		if (id != -1) {
			r = gm_RandomMod(4) * 2 + 6;
			cm_RequestCopyEntityData(*(int*) ((char*) ent + 4), id, r, 1);
		}
	}
	v = gm_RandomMod(4);
	d = (double) v + dbl_2_0;
	n = (int) (((double) gm_CalcPersonWealth(*ent) * d) *
	    dbl_0_01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, n);
	he_PostEntityMessage(*(int*) ((char*) ent + 4), *(int*) ((char*) ent + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) request, (char) gm_ActiveTownIndex, n);
	return 0;
}
