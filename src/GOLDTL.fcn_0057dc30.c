// FUNCTION: GOLDTL 0x57dc30
// SIZE: 258

#include <string.h>

// SIZE 0x10
struct offer {
	int good;
	int b;
	int c;
	char* seller;
};

// SIZE 0xc
struct level {
	int value;
	int b;
	int c;
};

extern unsigned char g_773d75;

unsigned short __cdecl fcn_005b56e0(int, int);
void __cdecl fcn_004a51d0(char*, int, struct offer*, struct level*);
float __cdecl fcn_0050bb50(int, unsigned char);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);

void __cdecl fcn_0057dc30(char* h)
{
	struct level lv;
	struct offer o;

	memset(&o, 0, sizeof(o));
	o.good = fcn_005b56e0(3, 6);
	fcn_004a51d0(h, 1, &o, &lv);
	if (o.seller != 0) {
		if (*(int*) (o.seller + 0xe) >= 3) {
			fcn_004c51a0(*(int*) (h + 4), -1, g_773d75, (int) fcn_0050bb50((unsigned short) o.good, g_773d75));
		} else {
			fcn_004c51f0(*(int*) (h + 4), -1, o.good, 1, g_773d75, 0);
		}
	} else if (lv.value >= 6) {
		fcn_004c51a0(*(int*) (h + 4), -1, g_773d75, (int) fcn_0050bb50(o.good, g_773d75));
	} else {
		fcn_004c51f0(*(int*) (h + 4), -1, o.good, 1, g_773d75, 0);
	}
}
