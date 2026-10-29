/* ADDRESS: GOLDTL 0x004f5910 */
int __cdecl fcn_004f5910(int a, int b)
{
	int found;
	int* p;

	found = 0;
	for (p = (int*) 0x99f804; (int) p < 0x9a3804; p += 2) {
		if (p[-1] == a && p[0] == b) {
			found = 1;
			break;
		}
	}
	return found;
}
