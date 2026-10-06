// FUNCTION: GOLD 0x005a6340
// FUNCTION: GOLDTL 0x005af770

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

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

extern char* g_14abcd0;

int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005af550(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_005af770(int e)
{
	Req req;

	if (fcn_00525fb0(e) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		req.kind = 7;
		req.c = 0x90010;
		if (e != 0) {
			req.id = 0x727;
			fcn_0052a0c0(e, 0);
			fcn_005bdc30(1, &req, g_14abcd0, fcn_005af550, 0);
			fcn_0052a2d0();
			fcn_005305a0();
		}
	}
}
