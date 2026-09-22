// FUNCTION: GOLD 0x004556a0
// SIZE: 34
// fcn_004556a0 — while([0xfb98f4] != 0xfb9280) fcn_00455750([0xfb98f4]).

int __cdecl fcn_00455750(int);

void __cdecl fcn_004556a0(void)
{
	while (*(int*) 0xfb98f4 != 0xfb9280) {
		fcn_00455750(*(int*) 0xfb98f4);
	}
}
