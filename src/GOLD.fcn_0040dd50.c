// FUNCTION: GOLD 0x0040dd50
// SIZE: 52
// fcn_0040dd50 — store floats to globals; fcn_00453890(1); return 1.

int __cdecl fcn_00453890(int);

int __cdecl fcn_0040dd50(int* a, int* b, int* c)
{
	*(float*) 0x5fcc78 = (float) *a;
	*(float*) 0x5fcc7c = (float) *b;
	*(float*) 0x5fcc80 = (float) *c;
	fcn_00453890(1);
	return 1;
}
