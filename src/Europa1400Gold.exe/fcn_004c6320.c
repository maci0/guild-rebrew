// FUNCTION: GOLD 0x004c6320
// SIZE: 42
// fcn_004c6320 — x[0]=0x69; *(int*)(x+0x14)=*(int*)(a+2); fcn_004c39c0(&x).

int __cdecl fcn_004c39c0(void*);

void __cdecl fcn_004c6320(char* a)
{
	char x[0x9c];
	x[0] = 0x69;
	*(int*) (x + 0x14) = *(int*) (a + 2);
	fcn_004c39c0(&x);
}
