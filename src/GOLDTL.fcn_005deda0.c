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

extern __int64 g_666018;
extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5530(Msg*);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

static __inline void send_hit(int id)
{
	Msg s;

	s.type = 0x82;
	s.id = id;
	s.target = -1;
	s.x36 = 2;
	s.x58 = 3;
	s.f5c = -0.35f;
	s.x59 = 5;
	s.i64 = 0x30;
	fcn_004c5530(&s);
}

/* ADDRESS: GOLD 0x005d2870 */
/* ADDRESS: GOLDTL 0x005deda0 */

int __cdecl fcn_005deda0(char* e, char* a2)
{
	int out;
	Req req;
	char text[0x100];
	char msg[0x800];
	char* r;
	char* p;

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
		if (r != 0) {
			send_hit(*(int*) (r + 4));
			if (r[2] == 6 || r[2] == 7) {
				fcn_0051af00(msg, 0xffb);
				fcn_00545d40(*(int*) (r + 4), -1, msg, 0, 0x5fb, 0);
			}
			p = fcn_005c6220(**(unsigned short**) a2, &out);
			*(int*) (a2 + 0x10) = 1;
			fcn_0051af00(msg, 0xfe8, *(unsigned short*) (p + 0x18) + 1, *(unsigned short*) r);
			fcn_005dbe90(msg);
			return 1;
		}
	} else {
		r = fcn_00508e40(*(int*) (a2 + 4));
		if (r != 0) {
			send_hit(*(int*) (r + 4));
			if (r[2] == 6 || r[2] == 7) {
				fcn_0051af00(msg, 0xffb);
				fcn_00545d40(*(int*) (r + 4), -1, msg, 0, 0x5fb, 0);
			}
			return 1;
		}
	}
	return 0;
}
