void __cdecl main_RunGameLoop();


void __cdecl main_ExitToFrameHandler(int);

/* ADDRESS: GOLDDE 0x004b6d10 */
int __cdecl cm_ExExitToMainFrame(int a1, char* p)
{
	main_ExitToFrameHandler((int) main_RunGameLoop);
	if (p != 0) {
		*p = 1;
	}
	return 0;
}
