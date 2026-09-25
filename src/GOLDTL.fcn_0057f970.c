// FUNCTION: GOLD 0x005773a0
// SIZE: 47
// FUNCTION: GOLDTL 0x0057f970
// SIZE: 47

extern int* g_665f08;

int __cdecl fcn_0057ed10(int* m);

int __cdecl fcn_0057f970(int* m)
{
	if (m[0] == 0x20) {
		if (m[3] == 0x155 && g_665f08[15] == 3) {
			return 1;
		}
		return 0;
	}
	return fcn_0057ed10(m);
}
