extern int g_9ba2e0[0x20];
extern int d2_CurrentWindowId;
extern double g_662c38;

char __cdecl d3_GetObjectScreenRect(int, int*);
void __cdecl gm_FindOrCreateEntitySlot(int, int);
int __cdecl d2_CreateWindow(int, int, int, int, int);
void __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl gm_GetScaledEntitySkill(int, int, int);
void __cdecl d2_DrawSegmentedBar(int, int, int);
float __cdecl gm_GetEntityHealthRatio(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int);

/* ADDRESS: GOLDTL 0x004cfab0 */
/* ADDRESS: GOLDDE 0x004bcf90 */
void __cdecl d2_OpenEntityStatusPopup(int owner, int targetEntity)
{
	int rect[4];
	int w;
	int h;
	int x0;
	int y0;
	int slot;

	if (!d3_GetObjectScreenRect(*(int*) (*(int*) (targetEntity + 0x184) + 0x34), rect)) {
		return;
	}
	x0 = rect[0] - 0x10;
	y0 = rect[1] - 0x10;
	w = rect[2] - rect[0] + 0x20;
	if (w <= 0x6e) {
		w = 0x6e;
	}
	h = rect[3] - rect[1] + 0x20;
	for (slot = 0; slot < 0x20; slot++) {
		if (g_9ba2e0[slot] == -1) {
			gm_FindOrCreateEntitySlot(owner, targetEntity);
			g_9ba2e0[slot] = d2_CreateWindow(x0, y0, w, h, 0x10);
			d2_AddElementToWindow(0, 0, 0x7b0, d2_CurrentWindowId);
			d2_AddElementToWindow(w - 0x18, 0, 0x7b1, d2_CurrentWindowId);
			*(int*) (0x10161cc + d2_CurrentWindowId * 0x3cc) = 0x54;
			d2_DrawSegmentedBar(4, 4, gm_GetScaledEntitySkill(targetEntity, 3, 0x4df));
			d2_CreateGuiWindow(d2_AddWindowValueGauge(0, 0xe, 0x40, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId), 0, 0x64,
			    (int) (gm_GetEntityHealthRatio(targetEntity) * 100.0));
			return;
		}
	}
}
