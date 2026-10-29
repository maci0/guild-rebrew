/* ADDRESS: GOLDTL 0x00465560 */
int __cdecl fcn_00465560(char* a)
{
	if (a == 0) {
		return -102;
	}
	a = *(char**) (a + 0x7c);
	if (a == 0) {
		return -102;
	}
	return *(int*) (a + 0x5c) == 0;
}
