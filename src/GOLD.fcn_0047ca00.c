
// fcn_0047ca00 — r=fcn_0041e670(a,b,c); [0xf8a638] = (r<<16)|r.

int __cdecl fcn_0041e670(int, int, int);

void __cdecl fcn_0047ca00(int a, int b, int c)
{
	int r;
	r = fcn_0041e670(a, b, c);
	*(int*) 0xf8a638 = (r << 0x10) | r;
}
