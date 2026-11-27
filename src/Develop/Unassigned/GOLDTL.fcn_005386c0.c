

extern int (__stdcall *g_662274)(int, void*, int, int);

int __cdecl main_SetScreensaverActive(void* p)
{
	return g_662274(0x11, p, 0, 2);
}
