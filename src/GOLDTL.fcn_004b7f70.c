#include <string.h>

extern void* __cdecl fcn_00508e40(unsigned int);
extern int __cdecl fcn_005c6270(void*, int);
extern void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl gm_FindNextFilteredEntity(void);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl fcn_0050dac0(unsigned short);
extern int __cdecl fcn_0051af00(char*, int, int);
extern int __cdecl fcn_00545d40(int, int, char*, int, int, int);
extern int __cdecl fcn_004c51a0(int, int, int, int);
extern int __cdecl fcn_004c54c0(int, int, int, int);

/* Collects the entity ids in the given building's filter chain, drops repeated
 * ids, emits the remaining ones and announces the building's road segment. */
/* ADDRESS: GOLDTL 0x004b7f70 */
int __cdecl fcn_004b7f70(unsigned int* a0)
{
	unsigned short* ent;
	unsigned short r;
	int ids[16];
	char buf[1024];
	int cnt;
	int i;
	int j;
	int m;
	int id;
	int n;
	double d;

	cnt = 0;
	ent = (unsigned short*) fcn_00508e40(*a0);
	if (ent == 0)
		return 1;
	if (fcn_005c6270(ent, 0x290) != 0)
		return 0x400;
	n = (int) gm_StartFilteredEntitySearch(1, 5, 7);
	if (n != 0) {
		do {
			if (cnt >= 0x10)
				break;
			if (*(unsigned short*) (n + 0x27) != 0xffff) {
				ids[cnt] = *(int*) ((*(unsigned short*) (n + 0x27) & 0xffff) * 0x21c + 0x7f4ca4);
				cnt += 1;
			}
			n = (int) gm_FindNextFilteredEntity();
		} while (n != 0);
	}
	if (cnt == 0)
		return 0x400;
	for (i = 0; i < cnt - 1; i++) {
		for (m = i + 1; m < cnt; m++) {
			if (ids[i] == ids[m])
				ids[m] = -1;
		}
	}
	for (i = 0; i < cnt; i++) {
		id = ids[i];
		if (id != -1) {
			r = (unsigned short) gm_RandomMod(4);
			fcn_004c54c0(*(unsigned int*) (ent + 2), id, r * 2 + 6, 1);
		}
	}
	r = (unsigned short) gm_RandomMod(4);
	d = (double) r + *(double*) 0x662a48;
	id = fcn_0050dac0(*(unsigned short*) ent);
	i = (int) ((double) id * d * *(double*) 0x6640e8);
	fcn_0051af00(buf, *(unsigned short*) (a0 + 1) + 0x12e7, i);
	fcn_00545d40(*(unsigned int*) (ent + 2), *(unsigned int*) (ent + 2), buf,
		(int) strlen(buf) > 0x100, 0x603, 0);
	fcn_004c51a0(-1, *a0, *(unsigned char*) 0x773d75, i);
	return 0;
}
