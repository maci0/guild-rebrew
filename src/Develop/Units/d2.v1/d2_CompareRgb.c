
/* ADDRESS: GOLDTL 0x00475780 */
/* ADDRESS: GOLDDE 0x00467fd0 */
int __cdecl d2_CompareRgb(char* left, char* right)
{
	if (left[0] == right[0] && left[1] == right[1] && left[2] == right[2]) {
		return 0;
	}
	return 1;
}
