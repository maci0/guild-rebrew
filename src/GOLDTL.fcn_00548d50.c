// FUNCTION: GOLDTL 0x548d50
// SIZE: 432

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int player;
	int target;
	char pad10[0x18];
	struct pos14 when;
	unsigned char mode;
	char pad37[0x21];
	int who;
	int amount;
	char pad60[0x98];
};

// SIZE 0x24
struct stats {
	char pad0[0x18];
	int level;
	char pad1c[8];
};

extern struct pos14 g_7f4c00;
extern char* g_773da8;
extern float g_662a3c;
extern float g_6629c0;
extern float g_6628cc;
extern float g_6628a0;

unsigned short __cdecl fcn_0042e410(int);
void* __cdecl fcn_005463a0(int, ...);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl fcn_004f4830(int, struct stats*);
int __cdecl fcn_0050cf50(char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_00548d50(void)
{
	char* cand[3];
	struct stats info;
	struct msg m;
	char* a;
	char* b;
	char* c;
	char* pick;
	int n;
	int amount;
	int idx;

	if (g_7f4c00.a < 8) {
		return;
	}
	if (fcn_0042e410(4) != 0) {
		return;
	}
	if (fcn_005463a0(1, 0, 0x67) != 0) {
		return;
	}
	a = gm_StartFilteredEntitySearch(1, 0, 0x20);
	b = gm_StartFilteredEntitySearch(1, 0, 0x1e);
	c = gm_StartFilteredEntitySearch(1, 0, 0x1f);
	n = 0;
	if (a != 0 && *(short*) (a + 0x27) == *(short*) g_773da8) {
		cand[n++] = a;
	}
	if (b != 0 && *(short*) (b + 0x27) == *(short*) g_773da8) {
		cand[n++] = b;
	}
	if (c != 0 && *(short*) (c + 0x27) == *(short*) g_773da8) {
		cand[n++] = c;
	}
	if (n == 0) {
		return;
	}
	idx = fcn_0042e410(n);
	fcn_004f4830(7, &info);
	pick = cand[idx];
	amount = (int) ((*(int*) (pick + 0x65) + *(int*) (pick + 0x69)) * (((5 - info.level) * g_662a3c + g_6629c0) * g_6628cc));
	m.kind = 0x67;
	m.when = g_7f4c00;
	m.player = *(int*) (g_773da8 + 4);
	m.target = *(int*) (pick + 1);
	m.who = *(int*) (pick + 1);
	m.amount = *(int*) (pick + 0x69) + amount;
	if (m.amount <= 0) {
		n = fcn_0050cf50(pick, 0x64);
		m.amount = (int) ((gm_RandomFloat01() + g_6628a0) * n);
	}
	m.mode = 2;
	fcn_004c5530(&m);
}
