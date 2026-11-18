


void __cdecl fcn_004c4330(void*);

typedef struct
{
	int v[0x20];
} Body20;
// SIZE 0x80

void __cdecl fcn_004c6de0(Body20* source)
{
	char buf[0x9c];

	buf[0] = 0x67;
	*(Body20*) (buf + 0x10) = *source;
	fcn_004c4330(buf);
}
