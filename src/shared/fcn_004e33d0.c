// FUNCTION: GOLD 0x004e33d0
// SIZE: 28
// fcn_004e33d0 — if(![0x6f0d8c]) *(0x6f0dbc)=fcn_00413b30(arg).

int __cdecl fcn_00413b30(int);

void __cdecl fcn_004e33d0(int a)
{
	if (*(int*) 0x6f0d8c == 0) {
		*(int*) 0x6f0dbc = fcn_00413b30(a);
	}
}
