/* ADDRESS: GOLDTL 0x004239e0 */

int* __cdecl fcn_004239e0(void)
{
	int* p;
	int* result;

	result = 0;
	p = *(int**) 0x6b7d68;
	if (p != 0) {
		result = (int*) p[0x38 / 4];
		if (result != 0) {
			while (*(int**) ((char*) result + 0x104) != 0) {
				result = *(int**) ((char*) result + 0x104);
			}
		}
	}
	return result;
}
