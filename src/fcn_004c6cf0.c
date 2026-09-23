// FUNCTION: GOLDTL 0x4c6cf0
// SIZE: 53

void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[9];
} Body9;
// SIZE 0x24

void __cdecl fcn_004c6cf0(Body9* a1)
{
	char buf[0x9c];

	buf[0] = 0x63;
	*(Body9*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
