
/* ADDRESS: GOLDTL 0x004e51a0 */
int __cdecl fcn_004e51a0(char* a1, int count)
{
	int i;

	for (i = count - 1; i > 0; i--) {
		if (*(int*) (a1 + 0x34 + i * 4) != -1) {
			return i;
		}
	}
	return 0;
}
