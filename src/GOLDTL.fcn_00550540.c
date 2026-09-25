// FUNCTION: GOLD 0x00548590
// SIZE: 26
// FUNCTION: GOLDTL 0x550540
// SIZE: 26

int __cdecl fcn_00546190(int*);

int __cdecl fcn_00550540(int* a1)
{
	int v;

	v = *(int*) ((char*) a1 + 0x70);
	if (v == -2 || v == 0) {
		return fcn_00546190(a1);
	}
	return v;
}
