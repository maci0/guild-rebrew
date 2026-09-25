int __cdecl fcn_004f4830(int idx, void* dst);

// FUNCTION: GOLD 0x004915e0
// SIZE: 89
// FUNCTION: GOLDTL 0x490bb0
// SIZE: 89

int __cdecl fcn_00490bb0(char* e, int unused, int* out)
{
	int info[9];
	int n;
	int level;

	n = (int) ((*(float*) (e + 0xac) - 2.0f) * 5.0f);
	if (n < 4)
		level = n;
	else
		level = 4;
	fcn_004f4830(6, info);
	if (level != info[6]) {
		*out = level;
		return 1;
	}
	return 0;
}
