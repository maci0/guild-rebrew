


char* __cdecl d3_FindFreeSceneEntry(void);
extern char d3_SceneEntries[];

/* ADDRESS: GOLDDE 0x004bb6e0 */
char* __cdecl d3_LookupSceneEntry(int id)
{
	int i;
	int address;

	if (id == 0) {
		return 0;
	}
	for (i = 0, address = (int) d3_SceneEntries; address < (int) (d3_SceneEntries + 0x2b8); address += 0x57, i++) {
		if (*(int*) address == id) {
			return d3_SceneEntries + i * 87;
		}
	}
	return d3_FindFreeSceneEntry();
}
