// FUNCTION: GOLDTL 0x4c5040
// SIZE: 147

int __cdecl fcn_004c4330(char*);
char* __cdecl fcn_0064d530(char*, char*, int);

int __cdecl fcn_004c5040(int a, int b, short c, char d, int e, char f, char g, char* s1, char* s2)
{
	char buf[0x9c];

	buf[0] = 0xc;
	*(int*) (buf + 0x14) = a;
	*(int*) (buf + 0x18) = b;
	*(short*) (buf + 0x1c) = c;
	buf[0x1e] = d;
	*(int*) (buf + 0x1f) = e;
	buf[0x23] = f;
	buf[0x24] = g;
	fcn_0064d530(buf + 0x25, s1, 0x10);
	fcn_0064d530(buf + 0x35, s2, 0x10);
	return fcn_004c4330(buf);
}
