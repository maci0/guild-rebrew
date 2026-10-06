// FUNCTION: GOLD 0x00574390
// FUNCTION: GOLDTL 0x57c8d0

int __cdecl fcn_00546190(int*);

int __cdecl fcn_0057c8d0(int* a1)
{
	int v;

	v = *(int*) ((char*) a1 + 0x70);
	if (v == -1 || v == -2) {
		return fcn_00546190(a1);
	}
	return v;
}
