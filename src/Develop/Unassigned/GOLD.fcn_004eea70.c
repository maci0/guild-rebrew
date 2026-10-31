

// fcn_004eea70 — x[0]=0x6154436e; x[1]=*(int*)(a+1); fcn_004c6db0(&x).
// The GOLDTL twin at 0x4f0900 differs by one constant byte (0x...64), so it
// lives in GOLDTL.fcn_004eea70.c.

int __cdecl fcn_004c6db0(int*);

void __cdecl fcn_004eea70(char* a)
{
	int x[2];
	x[0] = 0x6154436e;
	x[1] = *(int*) (a + 1);
	fcn_004c6db0(x);
}

