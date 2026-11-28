#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
extern float flt_0_0;
extern float g_665bf4;
extern float g_665bf0;
extern float g_6652c8;
extern double g_664e60;

#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl gm_QueryEntities(int obj, int mode, ...);
int __cdecl gm_GetMsgField(char* pkt, char* q);
float __cdecl eval_ObjektPreis2Credits(int id, int pct);
char* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl gm_EvalEntityInventoryValue(unsigned char* o, int* out)
{
	BUILDING_PROTOTYPE *rec;
	float v;
	float sum;
	char* q;
	char* e;
	int c;

	rec = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*o];
	v = flt_0_0;
	if (*(unsigned short*) (o + 0x27) != 0xffff) {
		v = (float) gm_CalcPersonWealth(*(unsigned short*) (o + 0x27));
		if (g_665bf4 < v) {
			v = g_665bf4;
		}
	}
	if (rec->category == 2) {
		v *= g_665bf0;
	} else {
		v *= g_6652c8;
	}
	if (flt_0_0 > v) {
		v = flt_0_0;
	}
	out[0] = (int) v;
	sum = 0;
	q = gm_QueryEntities(*(int*) (o + 0x5d), 2, 6, 0, 0x2a);
	if (q != 0) {
		for (e = gm_QueryEntities(*(int*) (q + 0x14), 1, 5); e != 0; e = gm_NextEntityQueryMatch()) {
			c = (int) (gm_GetMsgField(q, e) * g_664e60);
			if (c < 1) {
				c = 1;
			}
			sum += eval_ObjektPreis2Credits(*(unsigned short*) e, 100) * c;
		}
	}
	out[1] = (int) sum;
	return 0;
}
