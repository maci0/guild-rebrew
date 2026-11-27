/* ADDRESS: GOLDTL 0x00437890 */
char* __cdecl d3_NextVisibleSceneNode(char* a)
{
	int c;

	c = *(int*) (a + 0x1fc);
	a = *(char**) (a + 0x1f4);
	if (c == 0) {
		while (a != 0 && (a[0x214] & 1) == 0) {
			a = *(char**) (a + 0x1f4);
		}
	}
	return a;
}
