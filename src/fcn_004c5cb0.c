// FUNCTION: GOLDTL 0x4c5cb0
// SIZE: 101

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Triple3;
// SIZE 0xc

void __cdecl fcn_004c5cb0(int a1, Triple3* a2, Triple3* a3)
{
	char buf[0x9c];

	buf[0] = 0x32;
	*(int*) (buf + 0x10) = a1;
	if (a2 != 0) {
		*(Triple3*) (buf + 0x14) = *a2;
	}
	if (a3 != 0) {
		*(Triple3*) (buf + 0x24) = *a3;
	}
	fcn_004c4330(buf);
}
