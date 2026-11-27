

void __cdecl d2_ReleaseSurfaceGroup(void*, int);

void __cdecl d2_ClearPreviewTexture(void)
{
	if (*(int*) 0x774a64 != 0) {
		d2_ReleaseSurfaceGroup((void*) *(int*) 0x774a64, 0);
		*(int*) 0x774a64 = 0;
	}
}
