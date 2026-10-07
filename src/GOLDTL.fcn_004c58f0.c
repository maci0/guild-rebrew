// FUNCTION: GOLDTL 0x4c58f0

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Triple;
// SIZE 0xc

void __cdecl fcn_004c58f0(int a1, int a2, int a3)
{
	char buf[0x9c];

	buf[0] = 0x25;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x18) = a3;
	fcn_004c4330(buf);
}
