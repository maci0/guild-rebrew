// FUNCTION: GOLD 0x005d2590
// FUNCTION: GOLDTL 0x005deac0

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
extern float g_662a6c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c6b20(int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005deac0(char* e, char* a2)
{
	Req req;
	char text[0x200];
	char msg[0x400];
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
	if (fcn_005c6270(r, 0x2c4) == 0 || gm_RandomFloat01() > g_662a6c) {
		fcn_004c6b20(*(int*) (r + 4), 1, 0);
	}
	*(int*) (a2 + 0x10) = 1;
	if (e[2] == 6) {
		fcn_0051af00(text, 0x10a9, *(unsigned short*) r);
		fcn_0051af00(msg, 0xfe8, text);
		fcn_005dbe90(msg);
	}
	return 1;
}
