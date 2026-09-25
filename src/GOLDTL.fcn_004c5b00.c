// FUNCTION: GOLDTL 0x4c5b00
// SIZE: 74

typedef struct
{
	short s;
	char c;
} ShortChar;
// SIZE 0x4

int __cdecl fcn_004c4330(void*);

int __cdecl fcn_004c5b00(int a1, int a2, ShortChar a3)
{
	char buf[0x9c];

	*(int*) (buf + 0x18) = a2;
	*(short*) (buf + 0x1c) = a3.s;
	buf[0] = 0x2d;
	buf[0x1e] = a3.c;
	*(int*) (buf + 0x14) = a1;
	return fcn_004c4330(buf);
}
