// FUNCTION: GOLD 0x00578020
// SIZE: 36
// fcn_00578020 — if([0x5eec60][0x68]!=-1){ fcn_004758e0(h); reset }.

int __cdecl fcn_004758e0(int);

void __cdecl fcn_00578020(void)
{
	if (*(int*) (*(char**) 0x5eec60 + 0x68) != -1) {
		fcn_004758e0(*(int*) (*(char**) 0x5eec60 + 0x68));
		*(int*) (*(char**) 0x5eec60 + 0x68) = 0xffffffff;
	}
}
