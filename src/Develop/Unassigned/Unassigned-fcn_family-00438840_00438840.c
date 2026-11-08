extern float g_1042ce4;
extern float g_1042a14;
extern float g_1042588;
extern float g_104328c;
extern char g_6b8060;
extern float g_10529d0;
extern float g_10421a0;
extern float g_1042a24;
extern float g_1042a28;
extern float g_10432a4;
extern float g_10529c8;
extern float g_1043288;
extern float g_10529c4;
extern float g_10529d4;
extern float g_10529d8;

void __cdecl fcn_00438da0(float, float, float, float, float, float, float, float, float);
void __cdecl fcn_00438af0(unsigned char);
typedef struct IDev IDev;
typedef struct IDevVtbl {
	void* slots[50];
	long (__stdcall* SetRenderState)(IDev*, int, float);
} IDevVtbl;
struct IDev {
	IDevVtbl* v;
};

extern void* g_6b5de0;
extern int g_6b805c;
extern float g_10425fc;
extern float g_104329c;

void __cdecl fcn_00438840(float, float);
void __cdecl fcn_00438da0(float, float, float, float, float, float, float, float, float);

/* ADDRESS: GOLD 0x0043a610 */
/* ADDRESS: GOLDTL 0x00438840 */
void __cdecl fcn_00438840(float a, float b)
{
	float lim;

	if (g_1042ce4 == a && g_1042a14 == b) {
		return;
	}
	g_1042588 = 255.0f / (b - a);
	g_1042ce4 = a;
	g_1042a14 = b;
	g_104328c = a * a;
	if (g_6b8060 != 0) {
		lim = g_10529d0;
	} else {
		g_10529d0 = g_10421a0;
		lim = g_10421a0;
	}
	if (b < lim) {
		fcn_00438da0(g_10529d8, g_10529d4, g_10529c4, g_1043288, g_10529c8, b, g_10432a4, g_1042a28, g_1042a24);
	}
	fcn_00438af0(0);
}

/* ADDRESS: GOLDTL 0x00438920 */
void __cdecl fcn_00438920(float a, float b, int c)
{
	char on;

	if (a < b) {
		on = 1;
		fcn_00438840(a, b);
		g_10425fc = a;
		g_104329c = b;
		((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x24, g_1042ce4);
		((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x25, g_1042a14);
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
