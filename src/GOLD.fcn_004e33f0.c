// FUNCTION: GOLD 0x004e33f0
// fcn_004e33f0 — if(![0x6f0d8c]){ fcn_00413d00([0x6f0dbc]); [0x6f0dbc]=0; }.

int __cdecl fcn_00413d00(int);

void __cdecl fcn_004e33f0(void)
{
	if (*(int*) 0x6f0d8c == 0) {
		fcn_00413d00(*(int*) 0x6f0dbc);
		*(int*) 0x6f0dbc = 0;
	}
}
