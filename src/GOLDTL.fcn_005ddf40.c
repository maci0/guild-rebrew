// FUNCTION: GOLD 0x005d1a10
// SIZE: 195
// FUNCTION: GOLDTL 0x005ddf40
// SIZE: 195

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

extern __int64 g_666018;
extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_005ddf40(char* e, char* a2)
{
	Req req;
	char text[0x100];
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		fcn_0051af00(text, 0x9c);
		req.c = (*(int*)&g_666018);
		req.a = 0;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		r = fcn_005cd440(&req, text, 0, 0);
	}
	else {
		r = fcn_00508e40(*(int*) (a2 + 4));
	}
	if (r == 0) {
		return 0;
	}
	fcn_004c5420(*(int*) (r + 4), 0x1cc, 4, 0x100000, 0);
	return 1;
}
