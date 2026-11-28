extern char gm_EntitySlotTable[];
#include <string.h>

extern float g_66291c;

float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
void __cdecl d2_BuildPersonStatusDesc(void*);
int __cdecl gm_MatchesTargetFilter(unsigned short, unsigned short, int, int);

/* ADDRESS: GOLDTL 0x005cb670 */
/* ADDRESS: GOLDDE 0x005ad100 */
int __cdecl d2_CollectHighFavorEntities(char* sourceRecord, int n, char* results, int a3)
{
	char* h;
	int count;
	int i;
	int t;
	float d;

	count = 0;
	if (n == 0) {
		h = (char*) &gm_EntitySlotTable;
		while ((int) h < ((int) &gm_EntitySlotTable + 0x65400)) {
			if (h != sourceRecord && *(unsigned short*) h != 0xffff
			    && *(unsigned char*) (h + 2) >= 2 && *(unsigned char*) (h + 2) <= 7) {
				d = gm_CalcEntityFavor(*(unsigned short*) sourceRecord, *(unsigned short*) h, 1);
				if (d >= g_66291c && *(int*) (h + 0x210) != *(int*) (sourceRecord + 4)) {
					count++;
				}
			}
			h += 0x21c;
		}
		return count;
	}
	memset(results, 0, n * 0x38);
	h = (char*) &gm_EntitySlotTable;
	while ((int) h < ((int) &gm_EntitySlotTable + 0x65400)) {
		if (h != sourceRecord && *(unsigned short*) h != 0xffff
		    && *(unsigned char*) (h + 2) >= 2 && *(unsigned char*) (h + 2) <= 7) {
			d = gm_CalcEntityFavor(*(unsigned short*) sourceRecord, *(unsigned short*) h, 1);
			if (d >= g_66291c && *(int*) (h + 0x210) != *(int*) (sourceRecord + 4)) {
				if ((float) *(int*) (results + n * 0x38 - 0xc) < d) {
					*(int*) (results + n * 0x38 - 0x38) = (int) h;
					*(int*) (results + n * 0x38 - 0xc) = (int) d;
					count++;
					for (i = n - 1; i != 0; i--) {
						if (*(int*) (results + (i - 1) * 0x38 + 0x2c) < *(int*) (results + i * 0x38 + 0x2c)) {
							d = (float) *(int*) (results + (i - 1) * 0x38 + 0x2c);
							t = *(int*) (results + (i - 1) * 0x38);
							*(int*) (results + (i - 1) * 0x38) = *(int*) (results + i * 0x38);
							*(int*) (results + (i - 1) * 0x38 + 0x2c) = *(int*) (results + i * 0x38 + 0x2c);
							*(int*) (results + i * 0x38) = t;
							*(int*) (results + i * 0x38 + 0x2c) = (int) d;
						}
					}
				}
			}
		}
		h += 0x21c;
	}
	if ((unsigned int) count >= (unsigned int) n) {
		count = n;
	}
	for (i = 0; i < count; i++) {
		d2_BuildPersonStatusDesc(results + i * 0x38);
		*(int*) (results + i * 0x38 + 0x30) = gm_MatchesTargetFilter(*(unsigned short*) sourceRecord,
			*(unsigned short*) *(int*) (results + i * 0x38), a3, 0);
	}
	return count;
}
