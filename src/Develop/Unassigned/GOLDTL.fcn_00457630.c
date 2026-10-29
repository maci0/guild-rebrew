/* Terrain patch submit.  Builds the patch diffuse colour from the owning
 * entity, then refills the patch vertex and index buffers: the terrain walk
 * (fcn_00457c10 with a map, fcn_00457f40 without one) for a cell rectangle,
 * or a single flat quad when the patch is not eligible for the walk.
 * Returns whether any index was written. */

typedef int (__stdcall *GOLDTL_BufferLock)(void*, int, int, void**, int);
typedef void (__stdcall *GOLDTL_BufferUnlock)(void*);
typedef unsigned long (__stdcall *GOLDTL_BufferRelease)(void*);
typedef unsigned long (__stdcall *GOLDTL_CreateBuffer)(void*, unsigned long,
	unsigned long, unsigned long, int, void**);

/* The buffer and device interfaces share this view; only the slots the
 * patch touches are named. */
typedef struct GOLDTL_BufferVtbl {
	char pad_00[0x08];
	GOLDTL_BufferRelease Release;   /* 0x08 */
	char pad_0c[0x20];
	GOLDTL_BufferLock Lock;         /* 0x2c */
	GOLDTL_BufferUnlock Unlock;     /* 0x30 */
} GOLDTL_BufferVtbl;

typedef struct GOLDTL_DeviceVtbl {
	char pad_00[0x5c];
	GOLDTL_CreateBuffer CreateVertexBuffer; /* 0x5c */
	GOLDTL_CreateBuffer CreateIndexBuffer;  /* 0x60 */
} GOLDTL_DeviceVtbl;

typedef struct GOLDTL_TerrainVertex {
	float x;                    /* 0x00 */
	float y;                    /* 0x04 */
	float z;                    /* 0x08 */
	unsigned long diffuse;      /* 0x0c */
	float u;                    /* 0x10 */
	float v;                    /* 0x14 */
} GOLDTL_TerrainVertex;

typedef struct GOLDTL_TileUv {
	float u;                    /* 0x00 */
	float du;                   /* 0x04 */
	float v;                    /* 0x08 */
	float dv;                   /* 0x0c */
} GOLDTL_TileUv;

extern void* g_6b5de0;
extern unsigned char g_6b89bc;
extern unsigned char g_1040600;
extern float g_6628a0;
extern float g_6628a4;
extern float g_6628cc;
extern float g_662c30;
extern unsigned long g_14ce728;

void* __cdecl fcn_00457c10(void* vb, void* ib, void* map, int step, int* rect,
	GOLDTL_TileUv* uv, unsigned long diffuse);
int __cdecl fcn_00457f40(void* vb, void* ib, int* rect, int stride, int base,
	float* offset, float* scale, GOLDTL_TileUv* uv, unsigned long diffuse);

/* Patch layout: 0x00 texture, 0x04 diffuse, 0x08 entity, 0x10 base,
 * 0x14 stride, 0x18 step, 0x2c scale, 0x3c offset, 0x4c..0x5c quad corners,
 * 0x60..0x6c cell rectangle, 0x80 vertex buffer, 0x84 index buffer,
 * 0x88/0x8c buffer capacities, 0x90/0x94 written counts, 0x98 skip flag.
 * The byte return matches the original: only al is defined on the 0 path. */
/* ADDRESS: GOLDTL 0x00457630 */
char __cdecl fcn_00457630(void* obj, void* map)
{
	char* s;
	void* vb;
	void* ib;
	void* verts;
	void* idxs;
	GOLDTL_BufferVtbl* ops;
	GOLDTL_DeviceVtbl* device;
	GOLDTL_TerrainVertex* v;
	unsigned short* idx;
	unsigned char* entity;
	GOLDTL_TileUv uv;
	unsigned long color;
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	float q;
	float u0;
	float v0;
	float du;
	float dv;
	float fw;
	float fh;
	float scale;
	int x0;
	int x1;
	int z0;
	int z1;
	int w;
	int h;
	int rect[4];
	int count;

	s = (char*) obj;
	verts = 0;
	idxs = 0;
	if (map != 0 && *(int*) (s + 0x18) == 0 && *(char*) (s + 0x98) == 0) {
		return 0;
	}

	entity = *(unsigned char**) (s + 0x08);
	if (g_6b89bc != 0) {
		cr = (unsigned char) (int) *(float*) (entity + 0x5c);
		cg = (unsigned char) (int) *(float*) (entity + 0x60);
		cb = (unsigned char) (int) *(float*) (entity + 0x64);
		ca = (unsigned char) (int) (*(float*) (entity + 0x94) * g_6628cc);
	} else {
		scale = *(float*) (entity + 0x94) * g_6628cc * g_662c30;
		cr = (unsigned char) (int) ((g_6628a4
			- *(float*) (entity + 0x5c)) * scale);
		cg = (unsigned char) (int) ((g_6628a4
			- *(float*) (entity + 0x60)) * scale);
		cb = (unsigned char) (int) ((g_6628a4
			- *(float*) (entity + 0x64)) * scale);
		ca = 0xff;
	}
	color = ((unsigned long) ca << 24) | ((unsigned long) cr << 16)
		| ((unsigned long) cg << 8) | (unsigned long) cb;
	*(int*) (s + 0x94) = 0;
	*(unsigned long*) (s + 0x04) = color;
	*(int*) (s + 0x90) = 0;

	if (g_1040600 != 0 && *(int*) (s + 0x10) != 0
		&& *(int*) (s + 0x14) != 0 && *(char*) (s + 0x98) == 0) {
		x0 = *(int*) (s + 0x60);
		if (x0 >= *(int*) (s + 0x14)) {
			return 0;
		}
		x1 = *(int*) (s + 0x64);
		if (x1 < 0) {
			return 0;
		}
		z0 = *(int*) (s + 0x68);
		if (z0 >= *(int*) (s + 0x14)) {
			return 0;
		}
		z1 = *(int*) (s + 0x6c);
		if (z1 < 0) {
			return 0;
		}
		w = x1 - x0;
		if (w <= 0) {
			return 0;
		}
		h = z1 - z0;
		if (h <= 0) {
			return 0;
		}

		/* texture inset: one half vertex of the still-integer texture
		 * dimension, spread over the cell rectangle */
		q = g_6628cc / (float) (unsigned long) *(int*) (*(char**) s + 0x64);
		u0 = q;
		v0 = g_6628a0 - q;
		fw = (float) w;
		du = (g_6628a0 - (q + q)) / fw;
		fh = (float) h;
		dv = -(g_6628a0 - (q + q)) / fh;

		if (x0 < 0) {
			u0 = (float) (0 - x0) / fw;
			x0 = 0;
		}
		if (x1 >= *(int*) (s + 0x14)) {
			x1 = *(int*) (s + 0x14) - 1;
		}
		if (z0 < 0) {
			v0 = (float) z0 / fh;
			z0 = 0;
		}
		if (z1 >= *(int*) (s + 0x14)) {
			z1 = *(int*) (s + 0x14) - 1;
		}
		w = x1 - x0;
		h = z1 - z0;

		ib = *(void**) (s + 0x84);
		if (ib != 0 && (*(int*) (s + 0x88) < (h + 1) * (w + 1)
			|| *(int*) (s + 0x8c) < h * w * 2)) {
			ops = *(GOLDTL_BufferVtbl**) (s + 0x84);
			g_14ce728 = ops->Release(ib);
			*(void**) (s + 0x84) = 0;
			ops = *(GOLDTL_BufferVtbl**) (s + 0x80);
			g_14ce728 = ops->Release(*(void**) (s + 0x80));
			*(void**) (s + 0x80) = 0;
		}
		if (*(void**) (s + 0x84) == 0) {
			count = (h + 1) * (w + 1);
			*(int*) (s + 0x88) = count;
			*(int*) (s + 0x8c) = h * w * 2;
			device = *(GOLDTL_DeviceVtbl**) g_6b5de0;
			device->CreateVertexBuffer(g_6b5de0,
				(unsigned long) count * 0x18, 0x208, 0x142, 0,
				(void**) (s + 0x80));
			device = *(GOLDTL_DeviceVtbl**) g_6b5de0;
			device->CreateIndexBuffer(g_6b5de0,
				(unsigned long) *(int*) (s + 0x8c) * 6, 0x208, 0x65,
				0, (void**) (s + 0x84));
		}
		ib = *(void**) (s + 0x84);
		if (ib != 0) {
			uv.u = u0;
			uv.du = du;
			uv.v = v0;
			uv.dv = dv;
			rect[0] = x0;
			rect[1] = x1;
			rect[2] = z0;
			rect[3] = z1;
			*(int*) (s + 0x94) = (w + 1) * (h + 1);
			if (map != 0) {
				*(int*) (s + 0x90) = (int) fcn_00457c10(
					*(void**) (s + 0x80), ib, map,
					*(int*) (s + 0x18), rect, &uv, color);
			} else {
				*(int*) (s + 0x90) = fcn_00457f40(
					*(void**) (s + 0x80), ib, rect,
					*(int*) (s + 0x14), *(int*) (s + 0x10),
					(float*) (s + 0x3c), (float*) (s + 0x2c),
					&uv, color);
			}
		}
		return (char) (*(int*) (s + 0x90) > 0);
	}

	/* fallback: one quad covering the patch corners */
	ib = *(void**) (s + 0x84);
	if (ib != 0 && (*(int*) (s + 0x88) < 4 || *(int*) (s + 0x8c) < 2)) {
		ops = *(GOLDTL_BufferVtbl**) (s + 0x84);
		g_14ce728 = ops->Release(ib);
		*(void**) (s + 0x84) = 0;
		ops = *(GOLDTL_BufferVtbl**) (s + 0x80);
		g_14ce728 = ops->Release(*(void**) (s + 0x80));
		*(void**) (s + 0x80) = 0;
	}
	if (*(void**) (s + 0x84) == 0) {
		*(int*) (s + 0x88) = 4;
		*(int*) (s + 0x8c) = 2;
		device = *(GOLDTL_DeviceVtbl**) g_6b5de0;
		device->CreateVertexBuffer(g_6b5de0, 0x60, 0x208, 0x142, 0,
			(void**) (s + 0x80));
		device = *(GOLDTL_DeviceVtbl**) g_6b5de0;
		device->CreateIndexBuffer(g_6b5de0,
			(unsigned long) *(int*) (s + 0x8c) * 6, 0x208, 0x65, 0,
			(void**) (s + 0x84));
	}
	vb = *(void**) (s + 0x80);
	ops = *(GOLDTL_BufferVtbl**) vb;
	ops->Lock(vb, 0, 0x60, &verts, 0x2000);
	*(int*) (s + 0x94) = 4;
	*(int*) (s + 0x90) = 2;
	ib = *(void**) (s + 0x84);
	ops = *(GOLDTL_BufferVtbl**) ib;
	ops->Lock(ib, 0, *(int*) (s + 0x90) * 6, &idxs, 0x2000);

	v = (GOLDTL_TerrainVertex*) verts;
	v->x = *(float*) (s + 0x4c);
	v->y = *(float*) (s + 0x5c);
	v->z = *(float*) (s + 0x58);
	v->diffuse = color;
	v->u = 0.0f;
	v->v = 1.0f;
	v++;
	v->x = *(float*) (s + 0x50);
	v->y = *(float*) (s + 0x5c);
	v->z = *(float*) (s + 0x58);
	v->diffuse = color;
	v->u = 1.0f;
	v->v = 1.0f;
	v++;
	v->x = *(float*) (s + 0x4c);
	v->y = *(float*) (s + 0x5c);
	v->z = *(float*) (s + 0x54);
	v->diffuse = color;
	v->u = 0.0f;
	v->v = 0.0f;
	v++;
	v->x = *(float*) (s + 0x50);
	v->y = *(float*) (s + 0x5c);
	v->z = *(float*) (s + 0x54);
	v->diffuse = color;
	v->u = 1.0f;
	v->v = 0.0f;

	idx = (unsigned short*) idxs;
	idx[0] = 0;
	idx[1] = 1;
	idx[2] = 2;
	idx[3] = 1;
	idx[4] = 3;
	idx[5] = 2;

	if (verts != 0) {
		vb = *(void**) (s + 0x80);
		ops = *(GOLDTL_BufferVtbl**) vb;
		ops->Unlock(vb);
	}
	if (idxs != 0) {
		ib = *(void**) (s + 0x84);
		ops = *(GOLDTL_BufferVtbl**) ib;
		ops->Unlock(ib);
	}
	return (char) (*(int*) (s + 0x90) > 0);
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

unsigned char _dpad_14ce728[344] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
