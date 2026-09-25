// FUNCTION: GOLDTL 0x422100
// SIZE: 62

void __cdecl fcn_004232f0(void);
void __cdecl fcn_0041ddd0(int);
int __cdecl fcn_0042a2d0(int);

void __cdecl fcn_00422100(void)
{
	fcn_004232f0();
	if (*(int*) 0x6b7e88 != 0) {
		fcn_0041ddd0(*(int*) 0x6b7e88);
		*(int*) 0x6b7e88 = 0;
	}
	if (*(int*) 0x6b7d7c != 0) {
		fcn_0042a2d0(*(int*) 0x6b7d7c);
		*(int*) 0x6b7d7c = 0;
	}
}
