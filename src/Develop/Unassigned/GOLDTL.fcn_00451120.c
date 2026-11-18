
/* ADDRESS: GOLDTL 0x00451120 */
int __cdecl fcn_00451120(float* lhs, float* rhs)
{
	if (*rhs > *lhs) {
		return 1;
	}
	if (*lhs > *rhs) {
		return -1;
	}
	return 0;
}
