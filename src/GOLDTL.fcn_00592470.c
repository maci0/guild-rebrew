#include "client_types.h"
// GLOBAL: GOLDTL 0x779d00
extern Slot_779d00 g_779d00[];
// GLOBAL: GOLD 0x6f5ec0
extern Slot_779d00 g_779d00[];
// GLOBAL: GOLDTL 0x7e2700
extern int g_7e2700;
// GLOBAL: GOLD 0x75e8c0
extern int g_7e2700;
// GLOBAL: GOLDTL 0x14cf72a
extern char g_14cf72a[];
// GLOBAL: GOLD 0x14681ea
extern char g_14cf72a[];
// GLOBAL: GOLDTL 0x14cf950
extern char g_14cf950;
// GLOBAL: GOLD 0x1468410
extern char g_14cf950;
// FUNCTION: GOLD 0x00589f60
// FUNCTION: GOLDTL 0x592470

void __cdecl fcn_00591ea0(void);
void __cdecl fcn_00591d00(void);
void __cdecl fcn_00591da0(int);

void __cdecl fcn_00592470(void)
{
	char c;
	int i;
	char* e;

	c = *(char*) ((char*)&g_14cf950);
	if (c != 0 && *(int*) ((char*)&g_7e2700) != 1) {
		if (c == 0x58) {
			fcn_00591ea0();
		}
		fcn_00591d00();
		i = 0;
		for (e = ((char*)g_779d00); (int) e < (int) g_779d00 + 0x84; e += 12) {
			if (*e == *(char*) ((char*)&g_14cf950) && *(char*) g_14cf72a != 0) {
				fcn_00591da0(i);
			}
			i++;
		}
	}
}
