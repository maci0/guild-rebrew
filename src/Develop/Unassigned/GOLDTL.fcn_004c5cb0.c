

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Triple3;
// SIZE 0xc

void __cdecl fcn_004c5cb0(int a1, Triple3* firstTriple, Triple3* secondTriple)
{
	char buf[0x9c];

	buf[0] = 0x32;
	*(int*) (buf + 0x10) = a1;
	if (firstTriple != 0) {
		*(Triple3*) (buf + 0x14) = *firstTriple;
	}
	if (secondTriple != 0) {
		*(Triple3*) (buf + 0x24) = *secondTriple;
	}
	fcn_004c4330(buf);
}
