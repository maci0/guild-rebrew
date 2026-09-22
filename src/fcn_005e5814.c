// FUNCTION: GOLD 0x005e5814
// SIZE: 45
// fcn_005e5814 — fcn_005e5841(a, b, k, d); return b.

int __cdecl fcn_005e5841(int, int, int, int);

int __cdecl fcn_005e5814(int a, int b, int c)
{
	fcn_005e5841(a, b, (c == 0xa && a < 0) ? 0xa : c, (c == 0xa && a < 0) ? 1 : 0);
	return b;
}
