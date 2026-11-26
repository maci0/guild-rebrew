


extern int g_7749d8;
extern unsigned char* g_7d1980[];
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl he_CancelInvalidBuildingAction(unsigned char*);

void __cdecl he_RunQueuedActions(void)
{
	int i;
	unsigned char* p;

	for (i = 0; i <= g_7749d8 && i < 0x100; i++) {
		p = g_7d1980[i];
		if (p != 0 && *p < 0xa7) {
			he_CancelInvalidBuildingAction(p);
			g_7dc440[*p](p);
		}
	}
}
