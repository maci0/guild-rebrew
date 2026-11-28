extern char g_14b58c4[];
extern char sv_ClickedObjekt[];


int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(void*, int, int);
void __cdecl d2_RunSeanceAction(int);

/* ADDRESS: GOLDDE 0x00575bc0 */
void __cdecl d2_RunFriedhofSeanceMenu(int a)
{
	int v;

	while (main_RunFrameLoop(d2_RunFriedhofSeanceMenu, 0x67fff)) {
		v = RegisterStatusText("contact_SEANCE", *(int*) &g_14b58c4, 0x16);
		if (*(int*) &sv_ClickedObjekt != 0 && *(int*) &sv_ClickedObjekt == v) {
			d2_RunSeanceAction(a);
		}
	}
}
