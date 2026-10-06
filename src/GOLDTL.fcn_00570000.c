extern unsigned short g_774970;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_77e0a0[];
extern short g_77e0a4;
extern int g_77e0a8;

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[0x164];
	unsigned char b164;
	char pad2[0xb7];
};

extern char g_7f4ca0[];

// FUNCTION: GOLD 0x00567c50
// FUNCTION: GOLDTL 0x570000

int __cdecl fcn_00507b00(int);
void __cdecl fcn_0056fe60(char*);

void __cdecl fcn_00570000(char* o)
{
	int k;

	k = fcn_00507b00(((struct s_7f4ca0*)g_7f4ca0)[g_774970].b164);
	if (k == 1 || k == 2 || k == 3) {
		fcn_0056fe60("help_events_hw");
	} else if (k == 5 || k == 6) {
		fcn_0056fe60("help_events_alpa");
	} else if (k == 7) {
		fcn_0056fe60("help_events_kirche");
	} else if (k == 4) {
		fcn_0056fe60("help_events_wirt");
	} else if (k == 11) {
		fcn_0056fe60("help_events_dieb");
	}
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	*(int*) (o + 0x52) = (*(int*)g_77e0a0);
	*(short*) (o + 0x56) = g_77e0a4;
	*(int*) (o + 0x58) = g_77e0a8;
}
