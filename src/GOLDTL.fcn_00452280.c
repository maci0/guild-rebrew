

typedef struct IDev IDev;
// SIZE 0x60
typedef struct IDevVtbl {
	void* slots[23];
	long (__stdcall* CreateVertexBuffer)(IDev*, unsigned int, unsigned long, unsigned long, int, void**);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern unsigned int g_14ce7cc;
extern unsigned int g_6b8710;
extern unsigned int g_6b8714;
extern int g_67bc4c;
extern void* g_6b5de0;
extern char g_1040640[];
extern char g_1040960[];
extern char* g_1040c74;
extern int g_1040954;
extern int g_1040c78;
extern char* g_1040958;
extern void* g_104095c;
extern int g_6b8718;

void __cdecl fcn_00452280(void)
{
	unsigned int fvf;
	unsigned int stride;

	fvf = ((g_14ce7cc & 0x100000) | 0x210000) >> 15;
	g_6b8710 = fvf;
	stride = ((fvf & 0x20) | 0x80) >> 3;
	g_1040c74 = g_1040640;
	g_1040954 = 0;
	g_1040c78 = 0;
	g_1040958 = g_1040960;
	g_6b8714 = stride;
	((IDev*)g_6b5de0)->v->CreateVertexBuffer(((IDev*)g_6b5de0), g_67bc4c * stride, 0x248, fvf, 0, &g_104095c);
	g_6b8718 = 0;
}
