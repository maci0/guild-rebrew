// FUNCTION: GOLDTL 0x40ec60

// fcn_0040dd50 — store floats to globals; fcn_00453890(1); return 1.

int __cdecl fcn_00453890(int);

int __cdecl fcn_0040dd50(int* a, int* b, int* c)
{
	*(float*) 0x67bbdc = (float) *a;
	*(float*) 0x67bbe0 = (float) *b;
	*(float*) 0x67bbe4 = (float) *c;
	fcn_00453890(1);
	return 1;
}
