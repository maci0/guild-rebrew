typedef struct D2_SURFACE_COM D2_SURFACE_COM;
typedef struct {
	char pad0[0x8];
	int(__stdcall* release)(D2_SURFACE_COM*);
} D2_SURFACE_COM_VTBL;
// SIZE 0xc
struct D2_SURFACE_COM {
	D2_SURFACE_COM_VTBL* vtbl;
};

typedef struct {
	char pad0[0x20];
	D2_SURFACE_COM* f20;
	D2_SURFACE_COM* f24;
	char pad28[0x14];
	int f3c;
	int f40;
} D2_SURFACE_REC;

int __cdecl d2_UnlockSurface(D2_SURFACE_REC*);
void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x00475f80 */
int __cdecl d2_ReleaseSurface(D2_SURFACE_REC* o)
{
	if (o == 0)
		return 0;
	if (o->f3c != 0)
		d2_UnlockSurface(o);
	if (o->f40 == 0) {
		if (o->f24 != 0)
			o->f24->vtbl->release(o->f24);
		if (o->f20 != 0)
			o->f20->vtbl->release(o->f20);
	}
	m_FreeTracked(o);
	return 1;
}
