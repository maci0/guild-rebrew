extern int g_774800;

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()


extern struct pos14 g_7f4c00;

// FUNCTION: GOLD 0x005743e0
// SIZE: 175
// FUNCTION: GOLDTL 0x57c920
// SIZE: 175

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0057c920(char* o)
{
	if (o[0x78] & 4) {
		return;
	}
	*(struct pos14*) (o + 0x44) = g_7f4c00;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	if (g_774800 != 0) {
		fcn_00500bb0((struct pos14*) (o + 0x52), 1, 0, 0);
	} else {
		fcn_00500bb0((struct pos14*) (o + 0x52), 0x18, 0, 0);
		*(short*) (o + 0x56) = fcn_0042e410(2) + 0x13;
	}
	*(int*) (o + 0x58) = 0;
	*(int*) (o + 0x84) = fcn_004c5620(0, o);
}
