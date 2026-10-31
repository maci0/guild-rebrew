
// fcn_004c4920 — x[0]=0x13; x[0x10]=a1; x[0x14]=a2; x[0x18]=a3; fcn_004c39c0(&x).

int __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c4920(int a1, int a2, int a3)
{
	char x[0x9c];
	x[0] = 0x13;
	*(int*) (x + 0x10) = a1;
	*(int*) (x + 0x14) = a2;
	*(int*) (x + 0x18) = a3;
	fcn_004c4330(&x);
}
