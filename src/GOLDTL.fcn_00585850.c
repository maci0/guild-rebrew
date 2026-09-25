// FUNCTION: GOLD 0x0057d190
// SIZE: 189
// FUNCTION: GOLDTL 0x00585850
// SIZE: 189

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0xf8
typedef struct {
	int h0;
	unsigned char kind;
	char p5[3];
	int owner;
	int entity;
	char p10[0x18];
	int a;
	int b;
	int c;
	short d;
	unsigned char flag;
	char p37[0x21];
	int v58;
	int v5c;
	int v60;
	int v64;
	int v68;
	char p6c[0x8c];
} Msg;

extern char g_7f4ca0[];
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

int __cdecl fcn_004ecf00(char*, int*, int*, int);
void __cdecl fcn_004c5530(Msg*);

int __cdecl fcn_00585850(char* e, int* list)
{
	int x;
	int y;
	Msg msg;

	if (fcn_004ecf00(e, &x, &y, 0) != 0) {
		return 0;
	}
	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x95;
	msg.owner = *(int*) (g_7f4ca0 + *(unsigned short*) (e + 0x27) * 540 + 4);
	msg.entity = *(int*) (e + 1);
	msg.a = g_7f4c00;
	msg.b = g_7f4c04;
	msg.c = g_7f4c08;
	msg.d = g_7f4c0c;
	msg.flag = 1;
	msg.v58 = *list;
	msg.v64 = *list;
	fcn_004c5530(&msg);
	return 1;
}
