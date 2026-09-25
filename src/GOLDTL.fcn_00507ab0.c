// FUNCTION: GOLD 0x00504a80
// SIZE: 68
// FUNCTION: GOLDTL 0x00507ab0
// SIZE: 68

char* __cdecl fcn_0050e4a0(int);
void* __cdecl fcn_00502cd0(int, int, int, ...);

void __cdecl fcn_00507ab0(int a)
{
	char* e;

	e = fcn_0050e4a0(a);
	if (a == 1) {
		fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	} else {
		fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x142);
	}
}
