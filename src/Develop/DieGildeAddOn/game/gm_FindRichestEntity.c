#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
int __cdecl gm_CalcPersonWealth(int idx);

/* ADDRESS: GOLDTL 0x004fd400 */
/* ADDRESS: GOLDDE 0x004e8f30 */
int __cdecl gm_FindRichestEntity(short* out, int* value)
{
	int* rec;
	int now;
	int limit;
	int best;
	int i;
	int v;
	unsigned char* p;

	rec = *(int**) 0x773d5c;
	now = gm_GameTime.a;
	best = -100000;
	limit = 0xffff;
	if (rec == 0 || *(int*) 0x69643c < now || *(unsigned short*) rec == 0xffff || ((unsigned char*) rec)[8] == 0) {
		*(int*) 0x69643c = now;
		i = 0;
		p = (unsigned char*) 0x7f4ca2;
		while ((int) p < 0x85a0a2) {
			if (*(unsigned short*) (p - 2) != 0xffff && *p < 0xa && p[6] > 0) {
				v = gm_CalcPersonWealth(i);
				if (v > best) {
					best = v;
					limit = i;
				}
			}
			p += 0x21c;
			i++;
		}
		if (limit != 0xffff) {
			rec = (int*) (0x7f4ca0 + limit * 0x21c);
			*(int*) 0x696440 = best;
			*(int**) 0x773d5c = rec;
		} else {
			*(int**) 0x773d5c = 0;
			*(int*) 0x696440 = 0xc80;
			goto no_record;
		}
	}
	if (rec != 0) {
		*out = *(short*) rec;
		*value = *(int*) 0x696440;
		return 1;
	}
no_record:
	*out = -1;
	*value = *(int*) 0x696440;
	return 0;
}
