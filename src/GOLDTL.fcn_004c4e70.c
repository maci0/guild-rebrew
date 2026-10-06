// FUNCTION: GOLD 0x004c4500
// FUNCTION: GOLDTL 0x4c4e70

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[0x20];
} Body20;
// SIZE 0x80

void __cdecl fcn_004c4e70(Body20* a1)
{
	char buf[0x9c];

	buf[0] = 9;
	*(Body20*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
