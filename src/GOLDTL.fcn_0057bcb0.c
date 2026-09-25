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

// FUNCTION: GOLDTL 0x57bcb0
// SIZE: 198

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004f4f60(int, int, int, int, int);

void __cdecl fcn_0057bcb0(char* o)
{
	char* x;
	int id;

	*(int*) (o + 0x70) = 0;
	if (o[0x78] & 4) {
		return;
	}
	*(struct pos14*) (o + 0x44) = g_7f4c00;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	x = fcn_00508e40(*(int*) (o + 0xb0));
	if (x == 0) {
		*(int*) (o + 0x84) = fcn_004c5620(-1, o);
		return;
	}
	if (*(char**) (x + 0x170) != 0) {
		id = *(int*) (*(char**) (x + 0x170) + 1);
	} else {
		id = -1;
	}
	fcn_004f4f60(0x1c, 1, *(int*) (o + 0xc), *(int*) (x + 4), id);
	*(int*) (o + 0x84) = fcn_004c5620(0, o);
}
