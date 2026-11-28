#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char g_99f6a0[];
extern int g_99f6e0;
extern int g_99f724;
extern int g_99f768;
extern int g_99f7ac;
extern int g_99f7f0;
extern int gm_QueuedCommandCount;
extern unsigned char* lpGebaeudePROT;
extern char* lpGebaeudeINST;

void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);
int __cdecl gm_CalcEntityTaxSlots(unsigned short id, int* out, int c);
void __cdecl cm_StepCommandQueue(void);
int __cdecl gm_ApplyFaithLaw(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);

/* ADDRESS: GOLDTL 0x004fd280 */
/* ADDRESS: GOLDDE 0x004e8db0 */
void __cdecl gm_AdvanceRoundCounters(int flag)
{
	char* p;
	char* ent;
	int vals[8];
	int i;
	int n;

	fcn_0064d740(g_99f6a0, g_99f6a0 + 4, 0x40);
	fcn_0064d740(g_99f6a0 + 0x44, g_99f6a0 + 0x48, 0x40);
	fcn_0064d740(g_99f6a0 + 0x88, g_99f6a0 + 0x8c, 0x40);
	fcn_0064d740(g_99f6a0 + 0xcc, g_99f6a0 + 0xd0, 0x40);
	fcn_0064d740(g_99f6a0 + 0x110, g_99f6a0 + 0x114, 0x40);
	g_99f6e0 = 0;
	g_99f724 = 0;
	g_99f768 = 0;
	g_99f7ac = 0;
	g_99f7f0 = 0;
	gm_QueuedCommandCount = 0;
	i = 0;
	p = (char*) 0x7f4e38;
	{
		int out[0xe];

		do {
			gm_CalcEntityTaxSlots((unsigned short) i, out, flag); *(int*) (p + 4) = 0; *(int*) p = 0;
			if (gm_QueuedCommandCount > 0x40) {
				cm_StepCommandQueue();
				gm_QueuedCommandCount = 0;
			}


			p += 0x21c;
			i++;
		} while ((int) p < 0x85a238);
	}
	if ((flag & 1) != 0) {
		gm_ApplyFaithLaw();
	}
	if ((flag & 1) != 0) {
		char* ptrs[8];

		ent = (char*) gm_StartFilteredEntitySearch(1, 5, 7);
		if (ent != 0) {
			n = 0;
			while (ent != 0 && n < 8) {
				if (*(unsigned short*) (ent + 0x27) != 0xffff) {
					vals[n] = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) ent].level;
					ptrs[n] = ent;
					n++;
				}
				ent = (char*) gm_FindNextFilteredEntity();
			}
		}
	}
	i = 0;
	do {
		*(int*) (lpGebaeudeINST + i + 0x4d) = 0;
		if (*(unsigned char*) (lpGebaeudeINST + i) >= 0xb && *(unsigned char*) (lpGebaeudeINST + i) <= 0xd) {
			*(int*) (lpGebaeudeINST + i + 0x69) = 0;
		}
		i += 0xa9;
	} while (i < 0xa900);
}
