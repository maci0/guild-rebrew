#include <string.h>

extern void* __cdecl gm_LookupEntityRecordById(unsigned int);
extern int __cdecl fcn_005c6270(void*, int);
extern void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl gm_FindNextFilteredEntity(void);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
extern int __cdecl io_FormatTextBuffer(char*, int, int);
extern void __cdecl fcn_004c51a0(int, int, char, int);
extern void __cdecl fcn_00545d40(int, int, void*, int, int, int);
extern void __cdecl fcn_004c54c0(int, int, int, int);

/* Collects the entity ids in the given building's filter chain, drops repeated
 * ids, emits the remaining ones and announces the building's road segment. */
/* ADDRESS: GOLDTL 0x004b7f70 */
int __cdecl fcn_004b7f70(unsigned int* a0)
{
	unsigned short* ent;
	unsigned short r;
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
	ent = (unsigned short*) gm_LookupEntityRecordById(*a0);
	if (ent == 0) {
		return 1;
	}
	if (fcn_005c6270(ent, 0x290) != 0) {
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
			r = (unsigned short) gm_RandomMod(4);
			fcn_004c54c0(*(int*) ((char*) ent + 4), id, r * 2 + 6, 1);
		}
	}
	v = gm_RandomMod(4);
	d = (double) v + *(double*) 0x662a48;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) ent) * d) *
	    *(double*) 0x6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7, n);
	fcn_00545d40(*(int*) ((char*) ent + 4), *(int*) ((char*) ent + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	fcn_004c51a0(-1, *(int*) a0, *(char*) 0x773d75, n);
	return 0;
}
