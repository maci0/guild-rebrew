typedef struct
{
	char pad00[0x38];
	int f38;
	char pad3c[0x3cc - 0x3c];
} D2_WINDOW_SURFACE_SLOT;

int __cdecl d2_GetResourceData(int a);
void __cdecl d2_DrawSpriteFromSet(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x00472fa0 */
void __cdecl d2_DrawResourceOnWindow(int x, int y, int resourceId)
{
	D2_WINDOW_SURFACE_SLOT* t;
	int resource;

	t = (D2_WINDOW_SURFACE_SLOT*) (0x1015f40 + 0x3cc * *(int*) 0x772514);
	resource = d2_GetResourceData(resourceId);
	d2_DrawSpriteFromSet(x, y, t->f38, resource, *(int*) 0x772568);
}
