
/* ADDRESS: GOLDTL 0x00413160 */
int __cdecl d3_FindFreeSceneContext(void)
{
	int i;
	int a;

	i = 0;
	for (a = 0x1043695; a < 0x1052d95; a += 0x3dc, i++) {
		if (*(char*) (a - 1) == 0 && *(char*) a == 0) {
			return i;
		}
	}
	return -1;
}
