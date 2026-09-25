// FUNCTION: GOLD 0x004c4650
// SIZE: 118
// FUNCTION: GOLDTL 0x4c4fc0
// SIZE: 118

int __cdecl fcn_004c4330(char*);

int __cdecl fcn_004c4fc0(char a, int b, int c, short d, int e, char f, char g, char h)
{
	char buf[0x9c];

	buf[0] = 0xb;
	buf[0x14] = a;
	*(int*) (buf + 0x15) = b;
	*(int*) (buf + 0x19) = c;
	*(short*) (buf + 0x1d) = d;
	*(int*) (buf + 0x1f) = e;
	buf[0x23] = f;
	buf[0x24] = g;
	buf[0x25] = h;
	return fcn_004c4330(buf);
}
