


void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[6];
} Body6;
// SIZE 0x18

void __cdecl fcn_004c6d30(Body6* a1)
{
	char buf[0x9c];

	buf[0] = 0x64;
	*(Body6*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
