
// fcn_004c47b0 — x[0]=0xe; *(short*)(x+0x14)=arg; fcn_004c39c0(&x).

int __cdecl fcn_004c39c0(void*);

void __cdecl fcn_004c47b0(short a)
{
	char x[0x9c];
	x[0] = 0xe;
	*(short*) (x + 0x14) = a;
	fcn_004c39c0(&x);
}
