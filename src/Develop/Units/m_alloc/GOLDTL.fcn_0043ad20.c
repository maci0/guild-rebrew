int __cdecl m_pool_clear();
int __cdecl fcn_00437270();
int __cdecl fcn_004372d0();
void __cdecl fcn_00438840(float a, float b);
int __cdecl fcn_004385e0();
int __cdecl fcn_00440f70();
int __cdecl fcn_00441400();
int __cdecl fcn_00441050();
float __cdecl fcn_004424c0();
int __cdecl fcn_00437160();
int __cdecl fcn_00450cb0();
void __cdecl fcn_004509c0(void);
int __cdecl fcn_00450e90();
int __cdecl fcn_00451df0();
int __cdecl fcn_00452bc0();
int __cdecl fcn_00456e50();
int __cdecl fcn_00458bf0();
int __cdecl fcn_00459530();

typedef struct Dev_43ad20 Dev_43ad20;
typedef struct DevVtbl_43ad20 {
	char pad0[0x90];
	int (__stdcall* Clear)(Dev_43ad20* self, int count, void* rects, int flags, int color, float z, int stencil);
	int (__stdcall* SetTransform)(Dev_43ad20* self, int state, void* m);
	char pad98[0xc8 - 0x98];
	int (__stdcall* SetRenderState)(Dev_43ad20* self, int state, int value);
	char padcc[0xf4 - 0xcc];
	int (__stdcall* SetTexture)(Dev_43ad20* self, int stage, int tex);
} DevVtbl_43ad20;
struct Dev_43ad20 {
	DevVtbl_43ad20* vtbl;
};

typedef struct Mesh_43ad20 Mesh_43ad20;
typedef struct MeshVtbl_43ad20 {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	int (__stdcall* DrawSubset)(Mesh_43ad20* self, int i);
} MeshVtbl_43ad20;
struct Mesh_43ad20 {
	MeshVtbl_43ad20* vtbl;
};

extern void* g_6b5de0;
#define DEV_43ad20 ((Dev_43ad20*) g_6b5de0)

/* ADDRESS: GOLDTL 0x0043ad20 */
void __cdecl fcn_0043ad20(char a0, int a1)
{
	int v3;
	int v10;
	int* outer;
	int* v12;
	float v15;
	int p6;

	v3 = *(int*) 0x6b86d4;
	if (*(int*) 0x6b86d4 < 0) {
		v3 = 0;
		*(int*) 0x6b86d4 = 0;
	}
	if (*(char*) 0x6b8018 && !v3 && *(int*) 0x6b8014) {
		v10 = 3;
		*(int*) 0x6b86d4 = 1;
		DEV_43ad20->vtbl->Clear(DEV_43ad20, 1, (void*) 0x1042570, 3, *(int*) 0x6b805c, 1.0f, 0);
		*(int*) 0x1043294 = 0;
		*(int*) 0x10432a0 = 0x501502f9;
		if (*(int*) 0x6b8300) {
			fcn_00441050(*(int*) 0x6b8300);
		}
		*(int*) 0x1043028 = 0;
		fcn_00450cb0(*(int*) 0x6b8014, (*(unsigned char*) 0x1052bd0 & 0x1c) != 0);
		if (a0) {
			fcn_004509c0();
		}
		if (*(unsigned char*) 0x1052bd0 & 0x1c) {
			fcn_00456e50();
		}
		if (*(int*) 0x6b8300) {
			if (*(char*) 0x6b8060 && *(char*) 0x6b8061) {
				v15 = fcn_004424c0(*(int*) 0x6b8300, *(int*) 0x6b8014 + 0x4c, *(int*) 0x6b8014 + 0x18c);
				if (v15 < *(float*) 0x104329c) {
					fcn_00438840((*(float*) 0x6628a0 - (*(float*) 0x104329c - v15) / *(float*) 0x104329c) * *(float*) 0x10425fc, v15);
				} else {
					fcn_00438840(*(float*) 0x10425fc, *(float*) 0x104329c);
				}
			}
			DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x24, *(int*) 0x1042ce4);
			DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x25, *(int*) 0x1042a14);
		}
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x8b, -1);
		fcn_00437160(*(char*) 0x6b8060, *(int*) 0x6b805c, 1);
		if (*(int*) 0x6b89c0) {
			fcn_00459530(*(int*) 0x6b89c0);
		}
		if (*(int*) 0x6b8300) {
			fcn_00441400(*(int*) 0x6b8300);
		}
		*(int*) 0x6b8054 = 0;
		*(int*) 0x6b8050 = 0;
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 1);
		for (v3 = *(int*) 0x6b86ec; v3; v3 = *(int*) (v3 + 0x1f0)) {
			fcn_004385e0(v3, 0);
		}
		if (*(int*) 0x1043028) {
			fcn_00451df0(*(int*) 0x1043028);
		}
		for (outer = (int*) *(int*) 0x6b8068; outer; outer = (int*) outer[10]) {
			DEV_43ad20->vtbl->SetTransform(DEV_43ad20, 0x100, (void*) outer[1]);
			if (outer[6] < 0) {
				fcn_00450e90(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0x1040cc0, 0x1040c80);
			} else {
				fcn_00450e90(outer[4], outer[5], *(int*) (*outer + 0x1cc) + 0x280, 0, 0);
			}
			v12 = outer;
			do {
				v3 = v12[3];
				DEV_43ad20->vtbl->SetTexture(DEV_43ad20, 0, *(int*) (v3 + 0x50));
				p6 = *(unsigned char*) ((int) v12 + 0x1e);
				fcn_004372d0(*(unsigned char*) ((int) v12 + 0x1c), (*(unsigned char*) (v3 + 0x54) & 1) * 2 | (p6 & 1), v12[8], (*(unsigned char*) (v3 + 0x54) >> 3) & 1, (p6 >> 1) & 1);
				if (!(*(unsigned char*) (v3 + 0x54) & 8) && ((unsigned int) v12[6] >> 0x1b & 1) != (unsigned int) (v10 == 2)) {
					v10 = (~v12[6] & 0x8000000U | 0x10000000) >> 0x1b;
					DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, v10);
				}
				((Mesh_43ad20*) v12[2])->vtbl->DrawSubset((Mesh_43ad20*) v12[2], v12[6] & 0x7ffffff);
				v12 = (int*) v12[9];
			} while (v12);
		}
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x16, (*(char*) 0x6b7ffe == 0) * 2 + 1);
		DEV_43ad20->vtbl->SetRenderState(DEV_43ad20, 0x89, 0);
		if (*(unsigned char*) 0x1052bd0 & 0x1c) {
			fcn_00458bf0(*(int*) 0x6b8014);
		}
		if (*(int*) 0x6b8300) {
			fcn_00440f70(*(int*) 0x6b8300, a1);
		}
		m_pool_clear(0x6b8064);
		*(int*) 0x6b8068 = 0;
		fcn_00452bc0();
		fcn_00437270();
		if (*(float*) 0x10432a0 == *(float*) 0x662c94) {
			*(int*) 0x10432a0 = 0;
		}
		*(int*) 0x6b8044 = *(int*) 0x1052bac;
		*(int*) 0x6b802c = *(int*) 0x1042a08;
		*(int*) 0x6b803c = *(int*) 0x1042a00;
		*(int*) 0x6b8030 = *(int*) 0x10432a8;
		*(int*) 0x6b86d4 -= 1;
		*(int*) 0x6b8040 = *(int*) 0x1042a04;
		*(int*) 0x6b8034 = 0;
		*(int*) 0x6b8038 = *(int*) 0x1052bb0;
	}
}
