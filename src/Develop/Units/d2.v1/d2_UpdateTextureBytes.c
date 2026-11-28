// SIZE 0x50
typedef struct {
	char pad0[0x4c];
	int f4c;
} D2_TEX_SIZE_OBJ;

int __cdecl d2_GetSurfaceDesc(D2_TEX_SIZE_OBJ*, void*);


/* ADDRESS: GOLDTL 0x004760e0 */
/* ADDRESS: GOLDDE 0x00468490 */
int __cdecl d2_UpdateTextureBytes(D2_TEX_SIZE_OBJ* tex)
{
	int desc[8];

	if (d2_GetSurfaceDesc(tex, desc) != 0) {
		tex->f4c = desc[4] + 0x5c;
		return 1;
	}
	return 0;
}
