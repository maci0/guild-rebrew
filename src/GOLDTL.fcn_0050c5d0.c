// FUNCTION: GOLD 0x005091d0
// FUNCTION: GOLDTL 0x0050c5d0

extern unsigned char* g_868050;
extern float g_6628a8;
extern float g_665bf4;
extern float g_665bf0;
extern float g_6652c8;
extern double g_664e60;

#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
int __cdecl gm_GetMsgField(char* pkt, char* q);
float __cdecl fcn_0050b980(int id, int pct);
char* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl fcn_0050c5d0(unsigned char* o, int* out)
{
	unsigned char* rec;
	float v;
	float sum;
	char* q;
	char* e;
	int c;

	rec = g_868050 + *o * 589;
	v = g_6628a8;
	if (*(unsigned short*) (o + 0x27) != 0xffff) {
		v = (float) gm_WalkEntityChain(*(unsigned short*) (o + 0x27));
		if (g_665bf4 < v) {
			v = g_665bf4;
		}
	}
	if (*rec == 2) {
		v *= g_665bf0;
	} else {
		v *= g_6652c8;
	}
	if (g_6628a8 > v) {
		v = g_6628a8;
	}
	out[0] = (int) v;
	sum = 0;
	q = fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x2a);
	if (q != 0) {
		for (e = fcn_00502cd0(*(int*) (q + 0x14), 1, 5); e != 0; e = gm_NextEntityQueryMatch()) {
			c = (int) (gm_GetMsgField(q, e) * g_664e60);
			if (c < 1) {
				c = 1;
			}
			sum += fcn_0050b980(*(unsigned short*) e, 100) * c;
		}
	}
	out[1] = (int) sum;
	return 0;
}
