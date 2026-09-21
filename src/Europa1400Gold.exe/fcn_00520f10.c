// FUNCTION: GOLD 0x00520f10
// SIZE: 44
// fcn_00520f10 — fcn_0042e970(0x520ef0, 0x47); memset 0x75e920 0x300B; memset 0x935c00 0x100B.

int __cdecl fcn_0042e970(int, int);

void __cdecl fcn_00520f10(void)
{
	fcn_0042e970(0x520ef0, 0x47);
	memset((void*) 0x75e920, 0, 0x300);
	memset((void*) 0x935c00, 0, 0x100);
}
