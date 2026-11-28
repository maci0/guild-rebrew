
/* ADDRESS: GOLDTL 0x004e51a0 */
/* ADDRESS: GOLDDE 0x004d19f0 */
int __cdecl cut_FindPrevActiveSlot(char* cutscene, int count)
{
	int i;

	for (i = count - 1; i > 0; i--) {
		if (*(int*) (cutscene + 0x34 + i * 4) != -1) {
			return i;
		}
	}
	return 0;
}
