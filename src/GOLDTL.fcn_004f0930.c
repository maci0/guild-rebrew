/* fcn_004f0930 — pass an 8-byte tagged pair plus the argument to a helper. */

int __cdecl fcn_004c6db0(void*);

// FUNCTION: GOLDTL 0x4f0930
int __cdecl fcn_004f0930(int a1)
{
	int pair[2];

	pair[0] = 0x6454436e;
	pair[1] = a1;
	return fcn_004c6db0(pair);
}
