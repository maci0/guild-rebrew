// FUNCTION: GOLDTL 0x438920
// SIZE: 234

typedef struct IDev IDev;
typedef struct IDevVtbl {
	void* slots[50];
	long (__stdcall* SetRenderState)(IDev*, int, float);
} IDevVtbl;
struct IDev {
	IDevVtbl* v;
};

extern IDev* g_6b5de0;
extern float g_1042ce4;
extern float g_1042a14;
extern char g_6b8060;
extern int g_6b805c;
extern float g_10425fc;
extern float g_104329c;
extern float g_10529d0;
extern float g_1042a24;
extern float g_1042a28;
extern float g_10432a4;
extern float g_10529c8;
extern float g_1043288;
extern float g_10529c4;
extern float g_10529d4;
extern float g_10529d8;

void __cdecl fcn_00438840(float, float);
void __cdecl fcn_00438da0(float, float, float, float, float, float, float, float, float);

void __cdecl fcn_00438920(float a, float b, int c)
{
	char on;

	if (a < b) {
		on = 1;
		fcn_00438840(a, b);
		g_10425fc = a;
		g_104329c = b;
		g_6b5de0->v->SetRenderState(g_6b5de0, 0x24, g_1042ce4);
		g_6b5de0->v->SetRenderState(g_6b5de0, 0x25, g_1042a14);
	} else {
		on = 0;
		if (g_6b8060 != 0) {
			fcn_00438da0(g_10529d8, g_10529d4, g_10529c4, g_1043288, g_10529c8, g_10529d0, g_10432a4, g_1042a28, g_1042a24);
		}
		g_10425fc = a;
		g_104329c = b;
	}
	g_6b8060 = on;
	g_6b805c = c;
}
