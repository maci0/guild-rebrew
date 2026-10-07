// FUNCTION: GOLDTL 0x458d20

typedef struct IDev IDev;
// SIZE 0x158
typedef struct IDevVtbl {
	void* slots[61];
	long (__stdcall* SetTexture)(IDev*, int, void*);
	void* slots2[9];
	long (__stdcall* DrawIndexedPrimitive)(IDev*, int, unsigned int, unsigned int, unsigned int, unsigned int);
	void* slots3[11];
	long (__stdcall* SetStreamSource)(IDev*, unsigned int, void*, unsigned int);
	void* slots4[1];
	long (__stdcall* SetIndices)(IDev*, void*, unsigned int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern void* g_6b5de0;
extern int g_1052bac;
extern int g_1042a08;

void __cdecl fcn_00458d20(char* o)
{
	int i;
	char* e;

	for (i = 0; i < 4; i++) {
		e = *(char**) (o + 0x1ec) + i * 0x9c + 0x1384;
		if (*(char**) e != 0 && *(int*) (e + 0x90) > 0) {
			((IDev*)g_6b5de0)->v->SetStreamSource(((IDev*)g_6b5de0), 0, *(void**) (e + 0x80), 0x18);
			((IDev*)g_6b5de0)->v->SetIndices(((IDev*)g_6b5de0), *(void**) (e + 0x84), 0);
			((IDev*)g_6b5de0)->v->SetTexture(((IDev*)g_6b5de0), 0, *(void**) (*(char**) e + 0x50));
			((IDev*)g_6b5de0)->v->DrawIndexedPrimitive(((IDev*)g_6b5de0), 4, 0, *(unsigned int*) (e + 0x94), 0, *(unsigned int*) (e + 0x90));
			g_1052bac += *(int*) (e + 0x94);
			g_1042a08 += *(int*) (e + 0x90);
		}
	}
}
