


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

extern char* g_14a558c;

char* __cdecl fcn_005bdc30(int, Req*, char*, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_005df500(char* e, char* a2)
{
	Req req;
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		req.size = 0x410;
		req.kind = 4;
		req.c = 0xa0400300;
		req.d = 1;
		req.a = 0;
		r = fcn_005bdc30(1, &req, g_14a558c, 0, 0);
	}
	else {
		r = gm_SearchTable67(*(int*) (a2 + 4));
	}
	if (r == 0) {
		return 0;
	}
	fcn_004c5420(*(int*) (r + 1), 0x5a, 2, 0x2000, 0);
	return 1;
}
