// FUNCTION: GOLDTL 0x4c3d50
// SIZE: 222

#pragma pack(1)
typedef struct node99 {
	char f0;
	char pad[0x90];
	struct node99* prev;
	struct node99* next;
} node99;
// SIZE 0x99

typedef struct {
	char f0;
	char f1;
	int f2;
	int f6;
} cell10;
// SIZE 0xa
#pragma pack()

extern int g_68a9dc;
extern node99 g_9bade0[0x2000];
extern node99* g_aed200;
extern int g_aed324;
extern char g_1005780;
extern int g_1005768;
extern int g_1005760;
extern cell10 g_fb5760[0x8000];
extern char* g_14cbca4;
extern int g_6b7fac;
extern int g_aecde4;

void __cdecl fcn_004c3f70(void);
int __cdecl fcn_004c3fa0(void);
void __cdecl fcn_00421050(void);

void __cdecl fcn_004c3d50(void)
{
	int i;

	g_68a9dc = -1;
	for (i = 0; i < 0x2000; i++) {
		g_9bade0[i].f0 = 0;
		if (i == 0)
			g_9bade0[0].prev = 0;
		else
			g_9bade0[i].prev = &g_9bade0[i - 1];
		if (i < 0x1fff)
			g_9bade0[i].next = &g_9bade0[i + 1];
		else
			g_9bade0[i].next = 0;
	}
	g_aed200 = g_9bade0;
	g_aed324 = 0;
	g_1005780 = 0;
	g_1005768 = 0;
	g_1005760 = 0;
	for (i = 0; i < 0x8000; i++) {
		g_fb5760[i].f2 = -1;
		g_fb5760[i].f0 = 1;
	}
	g_14cbca4 = &g_1005780;
	fcn_004c3f70();
	if (fcn_004c3fa0() != 0)
		fcn_00421050();
	g_aecde4 = g_6b7fac;
}
