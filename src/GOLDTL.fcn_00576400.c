unsigned short __cdecl fcn_0042e410(int);

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

// FUNCTION: GOLDTL 0x576400
// SIZE: 147

int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00576400(char* o)
{
	struct pos14* p;

	if (o[0x78] & 4) {
		return;
	}
	p = (struct pos14*) (o + 0x52);
	*p = g_7f4c00;
	if (*(unsigned short*) (o + 0x56) > 0x13) {
		((struct pos14*) (o + 0x52))->a++;
		*(short*) (o + 0x56) = 0xd;
	} else if (*(unsigned short*) (o + 0x56) < 9) {
		*(short*) (o + 0x56) = fcn_0042e410(8) + 9;
	}
	*(int*) (o + 0xac) = 0;
	*(int*) (o + 0xb0) = -1;
	*(int*) (o + 0xb4) = -1;
	*(int*) (o + 0x84) = fcn_004c5620(0, o);
}
