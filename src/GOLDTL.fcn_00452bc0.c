// FUNCTION: GOLDTL 0x452bc0

typedef struct IDev IDev;
// SIZE 0x150
typedef struct IDevVtbl {
	void* slots[50];
	long (__stdcall* SetRenderState)(IDev*, int, int);
	void* slots2[25];
	long (__stdcall* SetVertexShader)(IDev*, unsigned int);
	void* slots3[6];
	long (__stdcall* SetStreamSource)(IDev*, unsigned int, void*, unsigned int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern void* g_6b5de0;
extern unsigned int g_6b8714;
extern unsigned int g_6b8710;
extern void* g_104095c;
extern char* g_1040c74;
extern char g_1040640[];

void __cdecl fcn_00452740(char*);

void __cdecl fcn_00452bc0(void)
{
	char* p;
	char* next;

	((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x8d, 1);
	((IDev*)g_6b5de0)->v->SetStreamSource(((IDev*)g_6b5de0), 0, g_104095c, g_6b8714);
	((IDev*)g_6b5de0)->v->SetVertexShader(((IDev*)g_6b5de0), g_6b8710);
	for (p = g_1040c74; p != g_1040640; p = next) {
		next = *(char**) (p + 0x314);
		fcn_00452740(p);
	}
	((IDev*)g_6b5de0)->v->SetStreamSource(((IDev*)g_6b5de0), 0, 0, 0);
	((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x8d, 0);
}
