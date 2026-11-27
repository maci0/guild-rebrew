


float __cdecl gm_CalcWeightedLawFactor(void*);

int __cdecl gm_HasZeroLaw0x11To1cSum(void)
{
	char buf[0x30];

	if (gm_CalcWeightedLawFactor(buf) == 0.0f) {
		return 1;
	}
	return 0;
}
