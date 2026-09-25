// FUNCTION: GOLDTL 0x456e50
// SIZE: 148

typedef struct IDev IDev;
// SIZE 0xf8
typedef struct IDevVtbl {
	void* slots[37];
	long (__stdcall* SetTransform)(IDev*, int, void*);
	void* slots2[12];
	long (__stdcall* SetRenderState)(IDev*, int, int);
	void* slots3[10];
	long (__stdcall* SetTexture)(IDev*, int, void*);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern IDev* g_6b5de0;
extern char g_1040600;
extern char* g_6b86ec;
extern char* g_1041d00;
extern char g_1052c00[];

void __cdecl fcn_004372d0(int, int, int, int, int);
void __cdecl fcn_00456ef0(char*);

void __cdecl fcn_00456e50(void)
{
	char* p;

	fcn_004372d0(0xff, 0, 0, 0, 1);
	g_6b5de0->v->SetRenderState(g_6b5de0, 7, 0);
	g_6b5de0->v->SetTexture(g_6b5de0, 0, 0);
	if (g_1040600 != 0) {
		for (p = g_6b86ec; p != 0; p = *(char**) (p + 0x1f0)) {
			fcn_00456ef0(p);
		}
		for (p = g_1041d00; p != 0; p = *(char**) (p + 0x1f0)) {
			fcn_00456ef0(p);
		}
	}
	g_6b5de0->v->SetTransform(g_6b5de0, 3, g_1052c00);
}
