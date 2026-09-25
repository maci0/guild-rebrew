// FUNCTION: GOLD 0x005d30e0
// SIZE: 150
// FUNCTION: GOLDTL 0x005df610
// SIZE: 150

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

extern char g_6b5c60[];

char* __cdecl fcn_005bdc30(int, Req*, char*, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_005df610(char* e, char* a2)
{
	Req req;
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		req.size = 0x410;
		req.kind = 4;
		req.c = 0xa0747980;
		req.d = 1;
		req.a = 0;
		r = fcn_005bdc30(1, &req, g_6b5c60, 0, 0);
		if (r == 0) {
			return 0;
		}
	}
	else {
		r = gm_SearchTable67(*(int*) (a2 + 4));
		if (r == 0) {
			return 0;
		}
	}
	fcn_004c5420(*(int*) (r + 1), 0x5a, 2, 0x1000, 0);
	return 1;
}
