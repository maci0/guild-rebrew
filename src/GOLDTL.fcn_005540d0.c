int __cdecl fcn_004c5620(int, char*);

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

// FUNCTION: GOLD 0x0054c070
// SIZE: 145
// FUNCTION: GOLDTL 0x5540d0
// SIZE: 145

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_005540d0(char* o)
{
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xd4) = -1;
		o[0xdc] = 0;
		*(struct pos14*) (o + 0x44) = g_7f4c00;
		*(struct pos14*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((struct pos14*) (o + 0x52), 0, 1, 0);
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
