// FUNCTION: GOLD 0x005a6870
// FUNCTION: GOLDTL 0x005afca0

// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

extern char* g_14abce8;

int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005afa50(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_005afca0(int e)
{
	Req req;

	if (fcn_00525fb0(e) == 0 && e != 0) {
		req.a = 1;
		req.size = -1;
		req.kind = 6;
		req.c = 0xa0744300;
		req.d = 1;
		req.id = 0x727;
		fcn_0052a0c0(e, 0);
		fcn_005bdc30(1, &req, g_14abce8, fcn_005afa50, 0);
		fcn_0052a2d0();
		fcn_005305a0();
	}
}
