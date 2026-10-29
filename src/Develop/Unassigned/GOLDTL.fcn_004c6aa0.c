


void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[0x12];
} Body18;
// SIZE 0x48

void __cdecl fcn_004c6aa0(Body18* a1)
{
	char buf[0x9c];

	buf[0] = 0x59;
	*(Body18*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}
