// FUNCTION: GOLD 0x00594550
// SIZE: 99
// FUNCTION: GOLDTL 0x0059d310
// SIZE: 99

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

extern int g_14abad4;

void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005bdc30(int, Req*, int, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_0059d060(void);

void __cdecl fcn_0059d310(int a)
{
	Req req;

	memset(&req, 0, sizeof(req));
	req.d = 0;
	req.size = 0x400;
	req.kind = 7;
	req.c = 0x93810;
	fcn_0052a0c0(a, 0);
	fcn_005bdc30(1, &req, g_14abad4, (void*) fcn_0059d060, 0);
	fcn_0052a2d0();
	fcn_005305a0();
}
