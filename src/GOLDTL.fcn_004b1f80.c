// FUNCTION: GOLDTL 0x4b1f80
// SIZE: 147

typedef struct {
	int a;
	int b;
} pair8;
// SIZE 0x8

typedef struct {
	int flag;
	pair8 slot[8];
} rec44;
// SIZE 0x44

extern rec44 g_1007bc0[4];
extern unsigned char g_773d75;
extern char g_868060[];
extern char g_680890[];
extern int g_67fca0;
extern int g_67fca4;
extern int g_67fca8;
extern int g_67fcac;
extern int g_67fcb0;
extern int g_67fcb4;

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0042d670(char*);

void __cdecl fcn_004b1f80(void)
{
	char buf[0x40];
	int i;
	int j;

	for (i = 0; i < 4; i++) {
		g_1007bc0[i].flag = 1;
		for (j = 0; j < 4; j++) {
			g_1007bc0[i].slot[j].a = -1;
			g_1007bc0[i].slot[j].b = 0xffff;
		}
	}
	fcn_0064d41a(buf, g_680890, g_868060 + g_773d75 * 0x2f4);
	fcn_0042d670(buf);
	g_67fca0 = -1;
	g_67fca4 = -1;
	g_67fca8 = -1;
	g_67fcac = -1;
	g_67fcb0 = -1;
	g_67fcb4 = -1;
}
