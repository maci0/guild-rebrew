// FUNCTION: GOLD 0x004012e0
// SIZE: 55
// FUNCTION: GOLDTL 0x401320
// SIZE: 55
// Client twin of GOLD's fcn_00401320 (0x401320, 23 B): the client calls
// fcn_00401260 on four consecutive ints; GOLD calls fcn_00430e30 once.

void __cdecl fcn_00401260(int, int);

void __cdecl fcn_00401320(int a1, int* a2)
{
	fcn_00401260(a1, a2[0]);
	fcn_00401260(a1, a2[1]);
	fcn_00401260(a1, a2[2]);
	fcn_00401260(a1, a2[3]);
}
