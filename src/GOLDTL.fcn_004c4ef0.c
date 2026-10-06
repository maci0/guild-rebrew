// FUNCTION: GOLD 0x004c4580
// FUNCTION: GOLDTL 0x4c4ef0

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_0064d530(void*, int, int);

void __cdecl fcn_004c4ef0(int a1)
{
	char buf[0x9c];

	buf[0] = 6;
	fcn_0064d530(buf + 0x10, a1, 0x80);
	fcn_004c4330(buf);
}
