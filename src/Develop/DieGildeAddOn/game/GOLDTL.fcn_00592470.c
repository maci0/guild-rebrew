#include "client_types.h"
extern Slot_779d00 g_779d00[];
extern Slot_779d00 g_779d00[];
extern int g_7e2700;
extern int g_7e2700;
extern char g_14cf72a[];
extern char g_14cf72a[];
extern char g_14cf950;
extern char g_14cf950;



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
