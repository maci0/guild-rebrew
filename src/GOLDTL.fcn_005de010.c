// FUNCTION: GOLD 0x005d1ae0
// FUNCTION: GOLDTL 0x005de010

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
void __cdecl fcn_00508cf0(int, int*);
void __cdecl fcn_004c6ba0(int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005de010(unsigned char* e, char* a2)
{
	int ids[5];
	Req req;
	char text[0x200];
	char msg[0x800];
	char* r;
	int i;
	int* p;

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
	fcn_00508cf0(5, ids);
	for (i = 0; i < 5; i++) {
		if (e[ids[i] + 0x80] > 0x15) {
			goto found;
		}
	}
	goto done;
found:
	p = &ids[i];
	fcn_004c6ba0(*(int*) (r + 4), *p, -0x15);
	if (r[2] == 6 || r[2] == 7) {
		fcn_0051af00(msg, 0x100a, *p + 0x16b7);
		fcn_00545d40(*(int*) (r + 4), -1, msg, 0, 0x5fb, 0);
	}
	if (e[2] == 6) {
		fcn_0051af00(text, 0x1099, *(unsigned short*) r, *p + 0x16b7);
		fcn_0051af00(msg, 0xfe8, text);
		fcn_005dbe90(msg);
	}
done:
	*(int*) (a2 + 0x10) = 1;
	return 1;
}
