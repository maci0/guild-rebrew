// FUNCTION: GOLDTL 0x4f0900
// SIZE: 36
// fcn_004eea70 twin — same shape as fcn_004eea70 (GOLDTL 0x4f08d0 / GOLD
// 0x4eea70) but the leading constant is 0x6454436e instead of 0x6154436e.

int __cdecl fcn_004c6230(int*);

void __cdecl fcn_004eea70(char* a)
{
	int x[2];
	x[0] = 0x6454436e;
	x[1] = *(int*) (a + 1);
	fcn_004c6230(x);
}
