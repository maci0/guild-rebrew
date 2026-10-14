
// fcn_004c3600 — x[0]=3; *(int*)(x+0x14)=0xa03ef57c; *(int*)(x+0x18)=0; fcn_004c39c0(&x).

int __cdecl fcn_004c39c0(void*);

void __cdecl fcn_004c3600(void)
{
	char x[0x9c];
	x[0] = 3;
	*(int*) (x + 0x14) = 0xa03ef57c;
	*(int*) (x + 0x18) = 0;
	fcn_004c39c0(&x);
}
