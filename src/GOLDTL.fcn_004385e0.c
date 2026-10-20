/* Builds one renderable particle per visible entity slot: allocates the
 * pool record, fills its transform and colour fields and links it into the
 * active list, or re-submits an already lit slot through the device. */

extern void* g_6b5de0;
extern void* g_6b8064;
extern void* g_6b8068;
extern int g_1042a08;
extern int g_1052bac;
extern int g_6b8054;
extern int g_1043028;

void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
void* __cdecl fcn_00436930(char* o, float* r);
void __cdecl fcn_004372d0(unsigned char a, unsigned char b, int c, unsigned char d, unsigned char e);
void __cdecl fcn_00450e90(float a, float b, char* c, void* d, void* e);

/* ADDRESS: GOLDTL 0x004385e0 */
unsigned char __cdecl fcn_004385e0(int a0)
{
	int v1;
	int v2;
	int v16;
	int v17;
	int v13;
	int v9;
	float v14;
	float v15;
	int* rec;
	int* p;
	unsigned char flag;

	flag = 0;
	v17 = 0;
	v1 = *(int*) (a0 + 0x1cc);
	if (*(int*) (v1 + 0x318) == 0
	    || *(int*) (*(int*) (v1 + 0x318) + 0x264) == 0
	    || *(int*) (a0 + 0x1ec) == 0) {
		goto tail;
	}
	v16 = (int) fcn_00436930((char*) v1, &v14);
	if (*(unsigned char*) (*(int*) (v1 + 0x318) + 0x2a1) & 4) {
		g_1043028 = a0;
	}
	v2 = *(int*) (v1 + 0x318);
	v14 = v14 + *(float*) (v2 + 0x1dc);
	v15 = *(float*) (*(int*) (a0 + 0x1ec) + 0x15f8);
	if (*(int*) (a0 + 0x220) == 1) {
		v15 = -v15;
	}
	v9 = *(int*) (v2 + 0x1e4);
	for (v13 = 0; v13 < *(int*) (*(int*) (v1 + 0x318) + 0x1e4); v13++) {
		v2 = *(int*) (v1 + 0x318);
		rec = (int*) *(int*) (*(int*) (v1 + 0x31c) + (v9 + v13) * 4);
		if (v16 != *(int*) (v2 + 0x268)
		    && (*(unsigned char*) ((char*) rec + 0x58) != 0xff
			|| (*(unsigned char*) ((char*) rec + 0x5a) & 1))) {
			p = (int*) m_PoolAlloc(g_6b8064, 0x2c, 0x10);
			p[0] = a0;
			p[2] = v16;
			p[1] = *(int*) (a0 + 0x1ec) + 0x48;
			p[3] = (int) rec;
			p[5] = *(int*) &v15;
			p[4] = *(int*) &v14;
			p[6] = v13;
			if (*(unsigned char*) (a0 + 0x215) & 0x20) {
				p[7] = *(int*) (v1 + 0x49c);
			} else {
				p[7] = *(int*) ((char*) rec + 0x58);
			}
			p[8] = *(int*) ((char*) rec + 0x6c) | *(int*) (v1 + 0x324);
			p[9] = v17;
			if (v17 != 0) {
				p[10] = *(int*) (v17 + 0x28);
				v17 = (int) p;
			} else {
				p[10] = (int) g_6b8068;
				g_6b8068 = p;
			}
		} else {
			if (!flag) {
				fcn_00450e90(v14, v15, (char*) (v1 + 0x280), 0, 0);
				(*(void (__cdecl**)(void*, int, void*)) (*(int*) g_6b5de0 + 0x94))
				    (g_6b5de0, 0x100, (void*) (*(int*) (a0 + 0x1ec) + 0x48));
				flag = 1;
			}
			(*(void (__cdecl**)(void*, int, void*)) (*(int*) g_6b5de0 + 0xf4))
			    (g_6b5de0, 0, (void*) *(int*) ((char*) rec + 0x50));
			fcn_004372d0(*(unsigned char*) ((char*) rec + 0x58),
			    (*(unsigned char*) ((char*) rec + 0x54) & 1) * 2
				| (*(unsigned char*) ((char*) rec + 0x5a) & 1),
			    *(int*) ((char*) rec + 0x6c) | *(int*) (v1 + 0x324),
			    (*(unsigned char*) ((char*) rec + 0x54) >> 3) & 1,
			    (*(unsigned char*) ((char*) rec + 0x5a) >> 1) & 1);
			(*(void (__cdecl**)(int, int)) (*(int*) v16 + 0xc))(v16, v13);
		}
	}
tail:
	g_1052bac += *(int*) (v1 + 0x310);
	g_1042a08 += *(int*) (v1 + 0x314);
	g_6b8054++;
	return 1;
}
