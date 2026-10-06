// FUNCTION: GOLD 0x004c5d40
// FUNCTION: GOLDTL 0x4c68c0

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[5];
} Body5;
// SIZE 0x14

void __cdecl fcn_004c68c0(Body5* a1)
{
	char buf[0x9c];

	buf[0] = 0x53;
	*(Body5*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
