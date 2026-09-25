// FUNCTION: GOLDTL 0x55f1f0
// SIZE: 270

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

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
void __cdecl fcn_005015e0(int, unsigned char**, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0055f1f0(char* e)
{
	unsigned char* r;

	r = 0;
	*(struct pos14*) (e + 0xc0) = *(struct pos14*) (e + 0x44);
	fcn_00500bb0((struct pos14*) (e + 0xc0), 0, *(int*) (e + 0xb8) * *(int*) (e + 0xb0), 0);
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	fcn_00500bb0((struct pos14*) (e + 0x52), 0, 0, 1);
	fcn_005015e0(0, &r, 0, *(int*) (e + 0xac));
	if (r != 0) {
		if ((r[0x13] & 0x20) != 0) {
			fcn_00546190(e);
			return;
		}
		fcn_004c5420(*(int*) (r + 2), 0x13, 1, 0x20, 0);
	}
	*(struct pos14*) (e + 0x60) = g_7f4c00;
	*(int*) (e + 0xb4) = r[0x12] + *(int*) (e + 0xb0) < 100 ? r[0x12] + *(int*) (e + 0xb0) : 100;
}
