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

typedef struct {
	short w;
	char kind;
	char p3;
	int id;
} Obj;

// SIZE 0xf8
typedef struct {
	int h;
	unsigned char type;
	char p5[3];
	int id;
	int target;
	char p10[0x26];
	char x36;
	char p37[0x21];
	char x58;
	char x59;
	char p5a[2];
	float f5c;
	float f60;
	int i64;
	char p68[0x90];
} Msg;

extern int g_666018;
extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
Obj* __cdecl fcn_005cd440(Req*, char*, int, int);
Obj* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5530(Msg*);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

static __inline void send_hit(int id)
{
	Msg s;

	s.type = 0x82;
	s.id = id;
	s.target = -1;
	s.x36 = 2;
	s.x58 = 0;
	s.f5c = -0.16666667f;
	s.x59 = 4;
	s.f60 = -0.33333334f;
	s.i64 = 0x18;
	fcn_004c5530(&s);
}

// FUNCTION: GOLDTL 0x005dcbb0
// SIZE: 423

int __cdecl fcn_005dcbb0(char* e, char* a2)
{
	Req req;
	char text[0x100];
	char msg[0x800];
	Obj* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		fcn_0051af00(text, 0x9c);
		req.c = g_666018;
		req.a = 0;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		r = fcn_005cd440(&req, text, 0, 0);
		if (r != 0) {
			send_hit(r->id);
			if (r->kind == 6 || r->kind == 7) {
				fcn_0051af00(msg, 0xff6);
				fcn_00545d40(r->id, -1, msg, 0, 0x5fb, 0);
			}
			return 1;
		}
	} else {
		r = fcn_00508e40(*(int*) (a2 + 4));
		if (r != 0) {
			if (r->kind == 6 || r->kind == 7) {
				fcn_0051af00(msg, 0xff6);
				fcn_00545d40(r->id, -1, msg, 0, 0x5fb, 0);
			}
			return 1;
		}
	}
	return 0;
}
