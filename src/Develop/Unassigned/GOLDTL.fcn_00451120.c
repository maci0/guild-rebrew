
/* ADDRESS: GOLDTL 0x00451120 */
int __cdecl d3_CompareLightWeightDesc(float* lhs, float* rhs)
{
	if (*rhs > *lhs) {
		return 1;
	}
	if (*lhs > *rhs) {
		return -1;
	}
	return 0;
}
