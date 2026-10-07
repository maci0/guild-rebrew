// FUNCTION: GOLD 0x0044d1c0
// fcn_0044d1c0 — fcn_0044ce40(a); if(b) fcn_00450db0(a). (a=param2, b=param4)

int __cdecl fcn_0044ce40(int);
int __cdecl fcn_00450db0(int);

void __cdecl fcn_0044d1c0(int u1, int a, int u2, char b)
{
	(void) u1; (void) u2;
	fcn_0044ce40(a);
	if (b != 0) {
		fcn_00450db0(a);
	}
}
