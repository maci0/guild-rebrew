// SIZE 0x8037
struct s_6b8300 {
	int kind;
	char pad[0x8032];
	unsigned char lo : 2;
	unsigned char mode : 3;
};

extern struct s_6b8300* g_6b8300;
extern int g_6b8010;
extern int g_1043370;
extern char g_699b08;
extern int g_67a370;

// FUNCTION: GOLDTL 0x5222a0
// SIZE: 234

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_004437a0(int);
void __cdecl fcn_00448360(int, int, void*);
void __cdecl fcn_0053f6a0(void);
int __cdecl fcn_0045b700(struct s_6b8300*, int, int);
void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_005224b0(void);
void __cdecl fcn_005224f0(void);

int __cdecl fcn_005222a0(int a)
{
	int save;

	fcn_004432d0(1, 0);
	fcn_004437a0(0);
	fcn_004432d0(0, 0);
	fcn_00448360(0, a, (void*) fcn_0053f6a0);
	fcn_004432d0(1, 0);
	fcn_004432d0(0, 0);
	if (g_6b8300->kind == 0x80) {
		g_1043370 = fcn_0045b700(g_6b8300, 0x100, 2);
	} else if (g_6b8300->kind == 0x40) {
		g_1043370 = fcn_0045b700(g_6b8300, 0x80, 2);
	} else {
		g_1043370 = fcn_0045b700(g_6b8300, 0x100, 2);
	}
	save = g_6b8010;
	fcn_004432d0(0, 0);
	if (g_6b8300 != 0) {
		g_6b8300->mode = g_699b08;
	}
	fcn_00437ac0(g_67a370, 0, 0x1c0, (void*) fcn_005224b0);
	fcn_00437ac0(g_67a370, 0, 0xc0, (void*) fcn_005224f0);
	fcn_004432d0(save, 0);
	return 1;
}
