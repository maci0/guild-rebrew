// FUNCTION: GOLD 0x004b4590
// SIZE: 40
// FUNCTION: GOLDTL 0x4b4700
// SIZE: 40

// fcn_004b4590 — fcn_00504ce0(a[0x164]) >= b[0x14].

int __cdecl fcn_00504ce0(int);

int __cdecl fcn_004b4590(char* a, char* b, int u)
{
	(void) u;
	return fcn_00504ce0((unsigned char) a[0x164]) >= *(int*) (b + 0x14);
}

