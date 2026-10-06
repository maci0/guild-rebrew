// FUNCTION: GOLD 0x004b3bd0
// fcn_004b3bd0 — set globals + fcn_004fe1e0(0xf82328, 0,0,0) + [0xf82340]=0.

int __cdecl fcn_004fe1e0(int, int, int, int);

void __cdecl fcn_004b3bd0(int b, int a)
{
	*(int*) 0xf82320 = a;
	*(int*) 0xf82324 = b;
	*(int*) 0xf82328 = 0;
	fcn_004fe1e0(0xf82328, 0, 0, 0);
	*(char*) 0xf82340 = 0;
}
