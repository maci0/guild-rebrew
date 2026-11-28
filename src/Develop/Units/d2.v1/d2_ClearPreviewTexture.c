extern char g_774a64[];


void __cdecl d2_ReleaseSurfaceGroup(void*, int);

/* ADDRESS: GOLDDE 0x005a9f30 */
void __cdecl d2_ClearPreviewTexture(void)
{
	if (*(int*) &g_774a64 != 0) {
		d2_ReleaseSurfaceGroup((void*) *(int*) &g_774a64, 0);
		*(int*) &g_774a64 = 0;
	}
}
