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

// FUNCTION: GOLDTL 0x552220
// SIZE: 161

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

void __cdecl fcn_00552220(char* o)
{
	char* p;

	if (o[0x78] & 4) {
		return;
	}
	for (p = fcn_005463a0(1, 0, 0x59); p != 0; p = fcn_005462a0()) {
		if (p != o) {
			*(struct pos14*) (o + 0x52) = g_7f4c00;
			*(int*) (o + 0x84) = fcn_004c5620(-1, o);
			return;
		}
	}
	*(int*) (o + 0x70) = 5;
	*(struct pos14*) (o + 0x52) = *(struct pos14*) (o + 0x44);
	*(int*) (o + 0x84) = -1;
	fcn_004c5620(5, o);
}
