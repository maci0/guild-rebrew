extern char* g_1006920[];
extern int g_7728f4;

char* __cdecl fcn_0044c310(char* key, char* val);

/* ADDRESS: GOLDTL 0x004bcab0 */

char* __cdecl fcn_004bcab0(char* name)
{
	int index;
	char* found;

	found = fcn_0044c310(name, name);
	index = g_7728f4;
	g_1006920[index] = found;
	/* Plain reload is deleted; the native reads the slot back. */
	found = ((char* volatile*) g_1006920)[index];
	g_7728f4 = index + 1;
	return found;
}
