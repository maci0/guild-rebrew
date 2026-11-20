
// fcn_004e33d0 — if(![0x6f0d8c]) *(0x6f0dbc)=fcn_00413b30(arg).

int __cdecl d3_CreateRain(int);

void __cdecl fcn_004e33d0(int a)
{
	if (*(int*) 0x6f0d8c == 0) {
		*(int*) 0x6f0dbc = d3_CreateRain(a);
	}
}
