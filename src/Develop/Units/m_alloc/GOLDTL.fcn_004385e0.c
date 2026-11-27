/* Builds one renderable particle per visible entity slot: allocates the
 * pool record, fills its transform and colour fields and links it into the
 * active list, or re-submits an already lit slot through the device. */
extern int d3_RenderedVertexCount, g_1042a08; extern void* g_6b8068;
typedef struct {
	char pad0[0x1dc];
	float f1dc;
	int pad1e0;
	int count;
	char pad1e8[0x7c];
	int f264;
	int f268;
	char pad26c[0x35];
	unsigned char f2a1;
} Mesh4385e0;
typedef struct {
	char pad0[0x280];
	char f280[0x90];
	int f310;
	int f314;
	Mesh4385e0* mesh;
	int* f31c;
	int pad320;
	int f324;
	char pad328[0x174];
	int f49c;
} Obj4385e0;
typedef struct {
	int f00;
	int f04;
	int f08;
	int f0c;
	float f10;
	float f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
} Particle4385e0;
void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
void* __cdecl d3_GetObjectMesh(char* o, float* r);
void __cdecl fcn_004372d0(unsigned char a, unsigned char b, int c, unsigned char d, unsigned char e);
void __cdecl d3_SelectActiveObjectLights(float a, float b, char* c, void* d, void* e);

/* ADDRESS: GOLDTL 0x004385e0 */
unsigned char __cdecl fcn_004385e0(int a0)
{
	Obj4385e0* v1;
	Mesh4385e0* m;
	int v16;
	int v17;
	int slotIndex;
	float v14;
	float v15;
	int* rec;
	Particle4385e0* p;
	unsigned char flag;

	slotIndex = 0; v1 = *(Obj4385e0**) (a0 + 0x1cc);
	if (v1->mesh == 0
	    || v1->mesh->f264 == 0
	    || *(int*) (a0 + 0x1ec) == 0) {
		goto tail;
	}
	v16 = (int) d3_GetObjectMesh((char*) v1, &v14);
	v17 = 0;
	flag = 0;
	if (v1->mesh->f2a1 & 4) {
		*(int*) 0x1043028 = a0;
	}
	m = v1->mesh;
	v14 = v14 + m->f1dc;
	v15 = *(float*) (*(int*) (a0 + 0x1ec) + 0x15f8);
	if (*(int*) (a0 + 0x220) == 1) {
		v15 = -v15;
	}
	for (; slotIndex < m->count; slotIndex++, m = v1->mesh) {
		rec = (int*) v1->f31c[m->count + slotIndex];
		if (v16 != m->f268
		    && (*(unsigned char*) ((char*) rec + 0x58) < 0xff
			|| (*(unsigned char*) ((char*) rec + 0x5a) & 1))) {
			p = (Particle4385e0*) m_PoolAlloc((void*) 0x6b8064, 0x2c, 0x10);
			p->f00 = a0;
			p->f08 = v16;
			p->f04 = *(int*) (a0 + 0x1ec) + 0x48;
			p->f0c = (int) rec;
			p->f10 = v14;
			p->f14 = v15;
			p->f18 = slotIndex;
			p->f1c = (*(unsigned char*) (a0 + 0x215) & 0x20)
			    ? v1->f49c
			    : *(int*) ((char*) rec + 0x58);
			p->f20 = *(int*) ((char*) rec + 0x6c) | v1->f324;
			p->f24 = v17;
			if (v17 != 0) {
				p->f28 = *(int*) (v17 + 0x28);
				v17 = (int) p;
			} else {
				p->f28 = (int) g_6b8068;
				g_6b8068 = p;
			}
		} else {
			if (!flag) {
				d3_SelectActiveObjectLights(v14, v15, v1->f280, 0, 0);
				(*(void (__stdcall**)(void*, int, void*)) (*(int*) (*(int*) 0x6b5de0) + 0x94))
				    ((void*) *(int*) 0x6b5de0, 0x100,
					(void*) (*(int*) (a0 + 0x1ec) + 0x48));
				flag = 1;
			}
			(*(void (__stdcall**)(void*, int, void*)) (*(int*) (*(int*) 0x6b5de0) + 0xf4))
			    ((void*) *(int*) 0x6b5de0, 0,
				(void*) *(int*) ((char*) rec + 0x50));
			fcn_004372d0(*(unsigned char*) ((char*) rec + 0x58),
			    (*(unsigned char*) ((char*) rec + 0x54) & 1) * 2
				| (*(unsigned char*) ((char*) rec + 0x5a) & 1),
			    *(int*) ((char*) rec + 0x6c) | v1->f324,
			    (*(unsigned char*) ((char*) rec + 0x5a) >> 1) & 1,
			    (*(unsigned char*) ((char*) rec + 0x54) >> 3) & 1);
			(*(void (__stdcall**)(int, int)) (*(int*) v16 + 0xc))(v16, slotIndex);
		}
	}
tail:
	d3_RenderedVertexCount += v1->f310;
	(*(int*) 0x6b8054)++;
	g_1042a08 += v1->f314;
	return 1;
}
