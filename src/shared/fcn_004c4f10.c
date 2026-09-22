// FUNCTION: GOLD 0x004c4f10
// SIZE: 61
// fcn_004c4f10 — x[0]=0x25; x[0x14]=a2; x[0x18]=a1; x[0x20]=a3; fcn_004c39c0(&x).

int __cdecl fcn_004c39c0(void*);

void __cdecl fcn_004c4f10(int a1, int a2, int a3)
{
	char x[0x9c];
	x[0] = 0x25;
	*(int*) (x + 0x14) = a2;
	*(int*) (x + 0x18) = a1;
	*(int*) (x + 0x20) = a3;
	fcn_004c39c0(&x);
}
