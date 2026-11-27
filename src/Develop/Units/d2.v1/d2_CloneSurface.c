typedef struct {
	int f0;
	char pad4[0x18];
	int f1c;
	int f20;
	char pad24[0x38];
} D2_CLONE_SURFACE_SRC;
// SIZE 0x5c

typedef struct {
	char pad0[0x4];
	int f4;
	int f8;
} D2_CLONE_SURFACE_DST;

D2_CLONE_SURFACE_DST* __cdecl d2_CreateSurface(D2_CLONE_SURFACE_SRC*, int);
void __cdecl d2_BlitSurfaceToSurface(int, int, int, int, D2_CLONE_SURFACE_SRC*, int, int, D2_CLONE_SURFACE_DST*);


/* ADDRESS: GOLDTL 0x00476a00 */
D2_CLONE_SURFACE_DST* __cdecl d2_CloneSurface(D2_CLONE_SURFACE_SRC* req)
{
	D2_CLONE_SURFACE_SRC copy;
	D2_CLONE_SURFACE_DST* r;

	copy = *req;
	copy.f20 = 0;
	copy.f1c = 0;
	r = d2_CreateSurface(&copy, req->f0);
	d2_BlitSurfaceToSurface(0, 0, r->f4, r->f8, req, 0, 0, r);
	return r;
}
