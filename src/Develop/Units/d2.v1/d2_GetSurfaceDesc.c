typedef struct D2_TEX_COM D2_TEX_COM;
typedef struct {
	char pad0[0x38];
	int(__stdcall* f38)(D2_TEX_COM*, int, void*);
} D2_TEX_VTBL;
// SIZE 0x3c
struct D2_TEX_COM {
	D2_TEX_VTBL* vtbl;
};

typedef struct {
	char pad0[0x20];
	D2_TEX_COM* f20;
} D2_SURFACE_OBJ;


/* ADDRESS: GOLDTL 0x004760c0 */
int __cdecl d2_GetSurfaceDesc(D2_SURFACE_OBJ* surface, void* desc)
{
	D2_TEX_COM* com;

	com = surface->f20;
	if (com == 0)
		return 0;
	return com->vtbl->f38(com, 0, desc) == 0;
}
