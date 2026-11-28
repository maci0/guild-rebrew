


extern int g_7749d8;
extern unsigned char* g_7d1980[];
extern void (__cdecl* he_EventDispatchHandlers[])(unsigned char*);

void __cdecl he_CancelInvalidBuildingAction(unsigned char*);

/* ADDRESS: GOLDDE 0x0052d410 */
void __cdecl he_RunQueuedActions(void)
{
	int i;
	unsigned char* action;

	for (i = 0; i <= g_7749d8 && i < 0x100; i++) {
		action = g_7d1980[i];
		if (action != 0 && *action < 0xa7) {
			he_CancelInvalidBuildingAction(action);
			he_EventDispatchHandlers[*action](action);
		}
	}
}
