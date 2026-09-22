// FUNCTION: GOLDTL 0x439c60
// SIZE: 42

void __cdecl fcn_00438af0(int);

void __cdecl fcn_00439c60(int a1)
{
	if (a1 == *(int*) 0x6b8014) {
		return;
	}
	if (*(int*) (a1 + 0x218) != 3) {
		return;
	}
	*(int*) 0x6b8014 = a1;
	fcn_00438af0(0);
}
