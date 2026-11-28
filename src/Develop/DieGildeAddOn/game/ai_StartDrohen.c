#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"

unsigned short* __cdecl gm_QueryEntities(int container_id, int arg_count, ...);
int __cdecl ai_SelectBestMethod(int who, int idx, int arg, int* out1, int* out2);
int __cdecl ai_SelectDrohenTarget(char* e, int* a, int* b);
float __cdecl gm_CalcSkillDuelScore(char* a, char* b, int c);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0049c880 */
/* ADDRESS: GOLDDE 0x0048b2c0 */
int __cdecl ai_StartDrohen(int a0, unsigned short* a1, int a2, int* a3, int* a4)
{
	int v7[6];
	int v8[6];
	float v9;
	int method;
	char* p;
	char kind;

	(void) a0;
	if (a2 != 0) {
		return 0;
	}
	p = (char*) a1;
	kind = p[2];
	if (*(int*) (p + 0x170) == 0) {
		if (kind == 3) {
			if ((p[0x1e8] & 4) == 0) {
				return 0;
			}
			goto retry;
		}
		*(unsigned char*) v7 = 5;
		v7[1] = 4;
		v7[2] = 1;
		*(unsigned char*) v8 = 0;
		v8[1] = 0;
		v8[2] = 0;
	}
	else {
		if (kind == 3) {
			if ((p[0x1e8] & 4) == 0) {
				return 0;
			}
			goto retry;
		}
		if (gm_QueryEntities(*(int*) (*(char**) (p + 0x170) + 0x5d), 2, 6, 0, 0x15) != 0) {
			goto retry;
		}
		*(unsigned char*) v7 = 2;
		v7[1] = 0x15;
		v7[2] = 1;
		v7[5] = 0x3ee147ae;
		*(unsigned char*) v8 = 4;
		v8[1] = *(int*) (*(char**) (p + 0x170) + 1);
		v8[2] = 1;
	}
	method = ai_SelectBestMethod(0x28, *a1, 1, v7, v8);
	goto done;
retry:
	memset(v7, 0, sizeof(v7));
	memset(v8, 0, sizeof(v8));
	if (ai_SelectDrohenTarget(p, v7, v8) == 0) {
		return 0;
	}
	v9 = gm_CalcSkillDuelScore(p, ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[v8[4]]), 4);
	if (gm_RandomFloat01() + v9 >= 1.0f) {
		method = 0x28;
		goto copy_result;
	}
	*(unsigned char*) v7 = 4;
	v7[1] = 3; v7[5] = 0;
	v7[2] = 1;
	*(unsigned char*) v8 = 0;
	v8[1] = 0;
	v8[2] = 0;
	method = ai_SelectBestMethod(0x28, *a1, 0, v7, v8);
done:
	if (method == 0) {
		return 0;
	}
copy_result:
	memcpy(a3, v7, sizeof(v7));
	memcpy(a4, v8, sizeof(v8));
	return method;
}
