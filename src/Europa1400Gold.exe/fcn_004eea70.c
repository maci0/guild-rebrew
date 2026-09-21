// FUNCTION: GOLD 0x004eea70
// SIZE: 36
// fcn_004eea70 — x[0]=0x6154436e; x[1]=*(int*)(a+1); fcn_004c6230(&x).

int __cdecl fcn_004c6230(int*);

void __cdecl fcn_004eea70(char* a)
{
	int x[2];
	x[0] = 0x6154436e;
	x[1] = *(int*) (a + 1);
	fcn_004c6230(x);
}
