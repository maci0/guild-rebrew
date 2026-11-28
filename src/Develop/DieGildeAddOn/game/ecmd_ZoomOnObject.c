extern char g_6b5cbc[];
int __cdecl d3_FindSceneObject(int, int, int, int);
void __cdecl d3_AnimateCameraToNode(int, int);

/* ADDRESS: GOLDTL 0x0040f910 */
/* ADDRESS: GOLDDE 0x0040e710 */
int __cdecl ecmd_ZoomOnObject(int* a0, int* a1)
{
	int handle;

	if (*(int*) ((int) &g_6b5cbc + 0x2200) != 0 && *(int*) (*(int*) ((int) &g_6b5cbc + 0x2200) + 0x44) == (int) ecmd_ZoomOnObject) {
		if (*(int*) &g_6b5cbc != 0 || *(int*) ((int) &g_6b5cbc + 0x4) != 0) {
			*(int*) (*(int*) ((int) &g_6b5cbc + 0x21dc) + 0xc60) = (int) ecmd_ZoomOnObject;
			return 0;
		}
		return 0;
	}
	if (*(int*) (*(int*) ((int) &g_6b5cbc + 0x21dc) + 0xc84) == 1) {
		*(int*) (*(int*) ((int) &g_6b5cbc + 0x21dc) + 0xc60) = (int) ecmd_ZoomOnObject;
	}
	handle = d3_FindSceneObject(0, 0x160, 0, *a1);
	if (handle != 0) {
		d3_AnimateCameraToNode(handle, *a0 / 17);
	}
	return 1;
}
