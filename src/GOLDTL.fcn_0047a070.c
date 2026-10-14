/* ADDRESS: GOLDTL 0x0047a070 */

char* __cdecl fcn_0047a070(char* p, int i)
{
	if (p == 0) {
		return 0;
	}
	return p + *(int*) (p + i * 4 + 0x45);
}
