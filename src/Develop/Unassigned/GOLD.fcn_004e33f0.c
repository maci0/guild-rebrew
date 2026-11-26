
// fcn_004e33f0 — if(![0x6f0d8c]){ fcn_00413d00([0x6f0dbc]); [0x6f0dbc]=0; }.

int __cdecl d3_DestroyRain(int);

void __cdecl fcn_004e33f0(void)
{
	if (*(int*) 0x6f0d8c == 0) {
		d3_DestroyRain(*(int*) 0x6f0dbc);
		*(int*) 0x6f0dbc = 0;
	}
}
