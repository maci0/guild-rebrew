


char* __cdecl fcn_004cded0(void);
extern char g_9baae0[];

char* __cdecl d3_LookupSceneEntry(int id)
{
	int i;
	int address;

	if (id == 0) {
		return 0;
	}
	for (i = 0, address = (int) g_9baae0; address < (int) (g_9baae0 + 0x2b8); address += 0x57, i++) {
		if (*(int*) address == id) {
			return g_9baae0 + i * 87;
		}
	}
	return fcn_004cded0();
}
