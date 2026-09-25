// FUNCTION: GOLDTL 0x459a10
// SIZE: 125

typedef struct IUnk IUnk;
// SIZE 0xc
typedef struct IUnkVtbl {
	long (__stdcall* QueryInterface)(IUnk*, void*, void**);
	unsigned long (__stdcall* AddRef)(IUnk*);
	unsigned long (__stdcall* Release)(IUnk*);
} IUnkVtbl;
// SIZE 0x4
struct IUnk {
	IUnkVtbl* v;
};

typedef struct IDev IDev;
// SIZE 0x64
typedef struct IDevVtbl {
	void* slots[23];
	long (__stdcall* CreateVertexBuffer)(IDev*, unsigned int, unsigned long, unsigned long, int, IUnk**);
	long (__stdcall* CreateIndexBuffer)(IDev*, unsigned int, unsigned long, int, int, IUnk**);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern IDev* g_6b5de0;
extern unsigned long g_14ce728;

void __cdecl fcn_00459a10(IUnk** o)
{
	IUnk** ib;

	if (o == 0) {
		return;
	}
	if (o[0] != 0) {
		g_14ce728 = o[0]->v->Release(o[0]);
		o[0] = 0;
	}
	g_6b5de0->v->CreateVertexBuffer(g_6b5de0, 0x600, 0x228, 0x1c4, 0, o);
	ib = &o[1];
	if (*ib != 0) {
		g_14ce728 = (*ib)->v->Release(*ib);
		*ib = 0;
	}
	g_6b5de0->v->CreateIndexBuffer(g_6b5de0, 0x1a4, 0x228, 0x65, 0, ib);
	((int*) o)[3] = -1;
}
