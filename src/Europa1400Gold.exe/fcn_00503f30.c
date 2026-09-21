// FUNCTION: GOLD 0x00503f30
// SIZE: 32
// fcn_00503f30 — r=fcn_00504ad0(a); return (r in [0xa,0xe]) ? 0 : 2.

int __cdecl fcn_00504ad0(int);

int __cdecl fcn_00503f30(int a)
{
	int r;
	r = fcn_00504ad0(a);
	if (r >= 0xa && r <= 0xe) {
		return 0;
	}
	return 2;
}
