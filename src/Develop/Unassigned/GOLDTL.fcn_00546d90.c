


extern int g_7749d8;
extern unsigned char* g_7d1980[];
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl he_CancelInvalidBuildingAction(unsigned char*);

void __cdecl he_RunQueuedActions(void)
{
	int i;
	unsigned char* action;

	for (i = 0; i <= g_7749d8 && i < 0x100; i++) {
		action = g_7d1980[i];
		if (action != 0 && *action < 0xa7) {
			he_CancelInvalidBuildingAction(action);
			g_7dc440[*action](action);
		}
	}
}
