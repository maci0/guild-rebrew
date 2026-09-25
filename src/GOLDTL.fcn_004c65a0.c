// FUNCTION: GOLD 0x004c5ae0
// SIZE: 170
// FUNCTION: GOLDTL 0x4c65a0
// SIZE: 170

typedef struct {
	int v[4];
} quad16;
// SIZE 0x10

typedef struct {
	int v[3];
} tri12;
// SIZE 0xc

extern char g_68ae9c[];

int __cdecl fcn_004c4330(char*);
int __cdecl fcn_0064d41a(char*, char*, ...);

int __cdecl fcn_004c65a0(int a, int b, float* v, tri12* w)
{
	char buf[0x19c];

	buf[0] = 0x4c;
	if (b == 0)
		return -1;
	*(int*) (buf + 0x10) = a;
	buf[0x18] = (char) b;
	*(quad16*) (buf + 0x19) = *(quad16*) v;
	*(tri12*) (buf + 0x29) = *w;
	fcn_0064d41a(buf + 0x9c, g_68ae9c, v[0], v[1], v[2]);
	return fcn_004c4330(buf);
}
