


void __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Small3i;
// SIZE 0xc

void __cdecl fcn_004c6900(Small3i* a1)
{
	char buf[0x9c];

	buf[0] = 0x54;
	*(Small3i*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
