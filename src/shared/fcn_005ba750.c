// FUNCTION: GOLDTL 0x5c61c0
// SIZE: 30

// fcn_005ba750 — fcn_00476c60(); fcn_00472cd0([0x6abb00]); [0x6abb00]=-1.

int __cdecl fcn_00476c60(void);
int __cdecl fcn_00472cd0(int);

void __cdecl fcn_005ba750(void)
{
	fcn_00476c60();
	fcn_00472cd0(*(int*) 0x6abb00);
	*(int*) 0x6abb00 = 0xffffffff;
}
