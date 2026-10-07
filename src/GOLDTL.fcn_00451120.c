// FUNCTION: GOLDTL 0x451120

int __cdecl fcn_00451120(float* a1, float* a2)
{
	if (*a2 > *a1) {
		return 1;
	}
	if (*a1 > *a2) {
		return -1;
	}
	return 0;
}
