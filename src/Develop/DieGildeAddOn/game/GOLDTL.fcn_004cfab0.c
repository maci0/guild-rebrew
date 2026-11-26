extern int g_9ba2e0[0x20];
extern int d2_CurrentWindowId;
extern double g_662c38;

char __cdecl fcn_00443e10(int, int*);
void __cdecl gm_FindOrCreateEntitySlot(int, int);
int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl gm_GetScaledEntitySkill(int, int, int);
void __cdecl fcn_00534160(int, int, int);
float __cdecl fcn_004ff040(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);

/* ADDRESS: GOLDTL 0x004cfab0 */
void __cdecl fcn_004cfab0(int a0, int targetEntity)
{
	int rect[4];
	int w;
	int h;
	int x0;
	int y0;
	int slot;

	if (!fcn_00443e10(*(int*) (*(int*) (targetEntity + 0x184) + 0x34), rect)) {
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
			gm_FindOrCreateEntitySlot(a0, targetEntity);
			g_9ba2e0[slot] = fcn_0046e940(x0, y0, w, h, 0x10);
			d2_AddElementToWindow(0, 0, 0x7b0, d2_CurrentWindowId);
			d2_AddElementToWindow(w - 0x18, 0, 0x7b1, d2_CurrentWindowId);
			*(int*) (0x10161cc + d2_CurrentWindowId * 0x3cc) = 0x54;
			fcn_00534160(4, 4, gm_GetScaledEntitySkill(targetEntity, 3, 0x4df));
			fcn_00472380(fcn_004677e0(0, 0xe, 0x40, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId), 0, 0x64,
			    (int) (fcn_004ff040(targetEntity) * 100.0));
			return;
		}
	}
}
