// FUNCTION: GOLDTL 0x00429800
// SIZE: 209
// FUNCTION: GOLD 0x0042af30
// SIZE: 209

// SIZE 0xc98
typedef struct {
	char used;
	char pad1[0xc97];
} Ctx;

// SIZE 0x4c
typedef struct {
	char name[0x4c];
} Var;

extern char* g_6b7e94;
extern void* g_6b7e9c;
extern void* g_14cb8e0;
extern void* g_6b7ea0;
extern void* g_6b7ea4;
extern void* g_14cb8f0;
void __cdecl fcn_00429d30(Ctx* c);
void __cdecl fcn_0041ddd0(void* p);

void __cdecl fcn_00429800(void)
{
	int i;

	for (i = 0; i < 0x80; i++) {
		if ((*(Ctx**)&g_6b7e94)[i].used != 0) {
			fcn_00429d30(&(*(Ctx**)&g_6b7e94)[i]);
		}
	}
	for (i = 0; i < 0x100; i++) {
		(*(Var**)&g_6b7e9c)[i].name[0] = 0;
	}
	if (g_14cb8e0 != 0) {
		fcn_0041ddd0(g_14cb8e0);
		g_14cb8e0 = 0;
	}
	if ((*(Var**)&g_6b7e9c) != 0) {
		fcn_0041ddd0((*(Var**)&g_6b7e9c));
		(*(Var**)&g_6b7e9c) = 0;
	}
	if (g_6b7ea0 != 0) {
		fcn_0041ddd0(g_6b7ea0);
		g_6b7ea0 = 0;
	}
	if (g_6b7ea4 != 0) {
		fcn_0041ddd0(g_6b7ea4);
		g_6b7ea4 = 0;
	}
	if (g_14cb8f0 != 0) {
		fcn_0041ddd0(g_14cb8f0);
		g_14cb8f0 = 0;
	}
	if ((*(Ctx**)&g_6b7e94) != 0) {
		fcn_0041ddd0((*(Ctx**)&g_6b7e94));
		(*(Ctx**)&g_6b7e94) = 0;
	}
}
