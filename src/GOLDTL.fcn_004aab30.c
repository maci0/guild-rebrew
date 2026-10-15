extern char s_67fb40[];

char* __cdecl fcn_00508e40(int id);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_004c4ef0(char* s);

/* ADDRESS: GOLD 0x004aaa10 */
/* ADDRESS: GOLDTL 0x004aab30 */
int __cdecl fcn_004aab30(char* a1, int a2, char* x)
{
	char msg[0xf8];
	float f;
	char* p;

	if (x[0] != 7) {
		return 0;
	}
	p = fcn_00508e40(*(int*) (x + 4));
	if (!p) {
		return 0;
	}
	fcn_004c4eb0(s_67fb40);
	f = fcn_00507e70(a1, p, 4);
	if (gm_RandomFloat01() + f >= 1.0f) {
		msg[4] = 0x2e;
		*(int*) (msg + 8) = *(int*) (p + 4);
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
		*(int*) (msg + 0x58) = *(int*) (p + 4);
		fcn_004c5530(msg);
	}
	fcn_004c6ae0(*(int*) (a1 + 4), -2);
	fcn_004c4ef0(s_67fb40);
	return 1;
}
