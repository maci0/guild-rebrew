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

// FUNCTION: GOLDTL 0x553420
// SIZE: 108

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_00553420(char* o)
{
	*(int*) (o + 0x84) = -1;
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xb8) = -1;
		*(struct pos14*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0((struct pos14*) (o + 0x52), 0, 2, 0);
		*(int*) (o + 0x70) = 1;
		*(int*) (o + 0x84) = fcn_004c5620(1, o);
	}
}
