

// SIZE 0x18
typedef struct {
	unsigned char valid;
	char pad1[3];
	int v[5];
} Pos;

#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "client_method_registry.h"











extern char g_1008540[];

int __cdecl fcn_00495150(int);
void __cdecl fcn_00495120(int);
void __cdecl fcn_00495140(void);

int __cdecl ai_SelectBestMethod(int who, int idx, int arg, Pos *out1, Pos *out2)
{
	float best1;
	float best2;
	float s1;
	float s2;
	int i;
	int res2;
	int res1;
	Pos p1;
	Pos p2;
	Pos primaryFirst;
	Pos primarySecond;
	Pos secondaryFirst;
	Pos secondarySecond;
	ENTITY_RECORD *me;
	AM_METHOD *pl;
	int r;

	best1 = -1e30f;
	best2 = -1e30f;
	res1 = 0;
	res2 = 0;
	primaryFirst.valid = 0;
	secondaryFirst.valid = 0;
	me = &((ENTITY_RECORD*)g_7f4ca0)[idx];
	primarySecond.valid = 0;
	secondarySecond.valid = 0;
	if (fcn_00495150(who) != 0) {
		return 0;
	}
	if (me->unk_218 == 0) {
		me->unk_218 = 1;
	}
	for (i = 0; i < 73; i++) {
		pl = &((AM_METHOD*)g_1008540)[i];
		if (pl->type == 0 || pl->type == me->unk_132 || fcn_00495150(pl->type) != 0) {
			continue;
		}
		fcn_00495120(pl->type);
		p1 = *out1;
		p2 = *out2;
		if (pl->score != 0) {
			((void (__cdecl *)(float *, float *, int, ENTITY_RECORD *, int, Pos *, Pos *)) pl->score)(&s1, &s2, i, me, arg, &p1, &p2);
		}
		if (s1 >= best1 || s2 >= best2) {
			if (pl->start != 0) {
				r = ((int (__cdecl *)(int, ENTITY_RECORD *, int, Pos *, Pos *)) pl->start)(who, me, arg, &p1, &p2);
				if (r != 0) {
					if (s1 >= best1) {
						best1 = s1;
						res1 = r;
						primaryFirst = p1;
						primarySecond = p2;
					}
					if (s2 >= best2) {
						best2 = s2;
						res2 = r;
						secondaryFirst = p1;
						secondarySecond = p2;
					}
				}
			}
		}
		fcn_00495140();
	}
	if (best1 != 0.0f && best1 >= best2) {
		*out1 = primaryFirst;
		*out2 = primarySecond;
		return res1;
	}
	*out1 = secondaryFirst;
	*out2 = secondarySecond;
	return res2;
}
