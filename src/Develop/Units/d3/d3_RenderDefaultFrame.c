extern char g_6b8018[];
extern char d3_SceneRenderLock[];


void __cdecl d3_RenderFrame(int, int, int);

/* ADDRESS: GOLDDE 0x0043c460 */
void __cdecl d3_RenderDefaultFrame(void)
{
	if (*(char*) &g_6b8018 == 0) {
		return;
	}
	if (*(int*) &d3_SceneRenderLock > 0) {
		return;
	}
	d3_RenderFrame(0x40, 1, 1);
}
