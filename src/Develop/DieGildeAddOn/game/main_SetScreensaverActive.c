

extern int (__stdcall *g_662274)(int, void*, int, int);

/* ADDRESS: GOLDDE 0x0051fed0 */
int __cdecl main_SetScreensaverActive(void* p)
{
	return g_662274(0x11, p, 0, 2);
}
