// FUNCTION: GOLD 0x005defef
// SIZE: 25
// fcn_005defef — r = fcn_005e533f(a); if(r) fcn_005e5269(r); return r.

int __cdecl fcn_005e533f(int);
int __cdecl fcn_005e5269(int);

int __cdecl fcn_005defef(int a)
{
	int r;
	r = fcn_005e533f(a);
	if (r != 0) {
		fcn_005e5269(r);
	}
	return r;
}
