// FUNCTION: GOLD 0x005a5530
// FUNCTION: GOLDTL 0x005ae960

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

extern __int64 g_666018;
extern int g_66601c;
extern int g_14aba0c;

int __cdecl fcn_00525fb0(char*);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_005cd440(Req*, char*, int, void*);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_005ae6a0(void);

void __cdecl fcn_005ae960(char* a)
{
	Req req;
	char text[0x40];
	char* p;
	char* q;

	if (fcn_00525fb0(a) != 0) {
		return;
	}
	for (p = fcn_005463a0(1, 0, 0x3c); p != 0; p = fcn_005462a0()) {
		if (*(int*) (p + 0xb4) == *(int*) (a + 1)) {
			fcn_00526120(g_14aba0c, 0);
			return;
		}
	}
	for (p = fcn_005463a0(1, 0, 0x3d); p != 0; p = fcn_005462a0()) {
		if (*(int*) (p + 0xb0) == *(int*) (a + 1)) {
			q = fcn_00508e40(*(int*) (p + 0xac));
			if (q != 0 && (unsigned char) q[0x1b1] > 0) {
				fcn_00526120(g_14aba0c, 0);
				return;
			}
			*(int*) (p + 0x84) = fcn_004c5620(-1, p);
		}
	}
	memset(&req, 0, sizeof(req));
	memset(&req.pad[2], -1, 0x20);
	req.a = 0;
	req.size = 0x400;
	req.kind = 6;
	req.c = (*(int*)&g_666018);
	req.d = g_66601c;
	fcn_0051af00(text, 0x19b8);
	fcn_0052a0c0(a, 0);
	fcn_005cd440(&req, text, 0, (void*) fcn_005ae6a0);
	fcn_0052a2d0();
	fcn_00532ef0();
}
