extern char* g_1006920[];
extern int g_7728f4;

char* __cdecl fcn_0044c310(char* key, char* val);

void __cdecl fcn_0044c440(char*);
extern char g_6813e8[];
extern char g_6813dc[];
extern char g_68140c[];
extern char g_681430[];
extern char g_6813f4[];
extern char g_681420[];

void __cdecl fcn_004bcae0(void);
char* __cdecl fcn_004bcab0(char*);

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

/* ADDRESS: GOLDTL 0x004bcae0 */
void __cdecl fcn_004bcae0(void)
{
	int i;

	for (i = 0; i < g_7728f4; i++) {
		if (g_1006920[i] != 0)
			fcn_0044c440(g_1006920[i]);
		g_1006920[i] = 0;
	}
}

/* ADDRESS: GOLDTL 0x004bcb20 */
void __cdecl fcn_004bcb20(void)
{
	if (g_7728f4 != 0)
		fcn_004bcae0();
	fcn_004bcab0(g_6813e8);
	fcn_004bcab0(g_6813dc);
	fcn_004bcab0(g_68140c);
	fcn_004bcab0(g_681430);
	fcn_004bcab0(g_6813f4);
	fcn_004bcab0(g_681430);
	fcn_004bcab0(g_681420);
}
