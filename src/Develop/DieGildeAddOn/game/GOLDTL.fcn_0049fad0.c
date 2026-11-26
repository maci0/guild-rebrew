


#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"







extern unsigned char g_773d75;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl amt_CheckZunftLevel2Eligibility(char* e);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050d320(char* e, char k);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);


int __cdecl ai_StartZunftAufruhr(int a1, char* e, int a3, char* out)
{
	int v;
	int targetId;
	char* target;
	int count;
	int i;
	F8 f;

	if (a3 != 0) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	if (amt_CheckZunftLevel2Eligibility(e) != 1) {
		return 0;
	}
	v = (int) max(gm_WalkEntityChain(*(unsigned short*) e) * 0.01f, 160.0f);
	if (v > (int) (fcn_0050d320(e, (*(char*)&g_773d75)) * 0.22f)) {
		return 0;
	}
	f.mask = 0x807d4190;
	f.b = 1;
	if (fcn_004a5e60(e, 6, f, 0, (float) (gm_RandomMod(0x20) + 0x20), &targetId) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&target), 0, 0, targetId);
	if (target == 0) {
		return 0;
	}
	count = 0;
	for (i = 0; i < 768; i++) {
		if ((*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == target) {
			count++;
		}
	}
	if (count == 0) {
		return 0;
	}
	*(int*) (out + 0x10) = v;
	out[0] = 4;
	*(int*) (out + 4) = targetId;
	return 0x37;
}
