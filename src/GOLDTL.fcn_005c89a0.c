

typedef struct {
	int btn;
	int bar;
	int value_text;
	int name_text;
	int value;
	unsigned char* e;
} Row5c89;
// SIZE 0x18

typedef struct {
	char pad[0x18];
	int w;
	char pad2[0x2d8];
} Font5c89;
// SIZE 0x2f4

extern Row5c89 g_777d00[128];
extern int g_776c90;
extern int g_777ca0;
extern int g_778b00;
extern char g_1016198[];
extern char* g_1015ea0;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern char g_6ac878[];
extern char g_6ac870[];
extern char g_68be7c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_0050dc90(unsigned char*);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
void __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_0046fac0(int x, int y, char* text, int win);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_00467480(int x, int y, int a3, int a4, int a5, int win);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005c89a0(void)
{
	int n;
	char* m;
	char buf[0x100];
	int h;
	int k;
	unsigned char* e;

	n = 0;
	h = fcn_00470820(0, 0, g_6ac878);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1934);
	for (k = 0; k < 128; k++) {
		g_777d00[k].btn = -1;
		g_777d00[k].bar = -1;
		g_777d00[k].value_text = -1;
		g_777d00[k].name_text = -1;
		g_777d00[k].value = 0;
	}
	fcn_004727a0(h, 0);
	fcn_00533f40(0x206, 0x167, g_772514, fcn_00472830(h, 2), 0x3e, &g_776c90, &g_777ca0, &g_778b00);
	*(int*) (g_1016198 + g_772514 * 0x3cc + 0x160) = -1;
	*(int*) (g_1016198 + g_772514 * 0x3cc + 0x164) = -1;
	fcn_004727a0(h, 3);
	fcn_00519190(0x1935);
	fcn_004727a0(h, 4);
	fcn_00519190(0x1936);
	fcn_004727a0(h, 2);
	e = gm_StartFilteredEntitySearch(1, 4, g_774970);
	if (e != 0) {
		do {
			m = fcn_0050dc90(e);
			if (m != 0 && *(unsigned short*) m != g_774970) {
				fcn_004727a0(h, 2);
				g_777d00[n].btn = fcn_0046f740(0, n * 0x3e, *e + 0x427, g_772514);
				fcn_0051af00(buf, g_6ac870, *e * 14 + 0x48e, e + 5);
				g_777d00[n].name_text = fcn_0046fac0(0x40, n * 0x3e + 8, buf, g_772514);
				((Font5c89*)g_1015ea0)[g_777d00[n].name_text].w = 0xa0;
				fcn_00472900(g_777d00[n].name_text, 0x54);
				fcn_0051af00(buf, g_68be7c, *(int*) (m + 0x1b8));
				g_777d00[n].value_text = fcn_0046fac0(0x180, n * 0x3e + 0x14, buf, g_772514);
				g_777d00[n].bar = fcn_00467480(0xea, n * 0x3e + 0x14, 0x40, 0x40, 0x82, g_772514);
				fcn_00472380(g_777d00[n].bar, 0x3e8, 0x2328, fcn_0050b710(*(int*) (e + 0x39), g_773d75));
				g_777d00[n].value = fcn_00471f80(g_777d00[n].bar);
				g_777d00[n].e = e;
				n++;
			}
			e = gm_AddObjekt();
		} while (e != 0);
	}
	if (n == 0) {
		fcn_00471e30(h);
		return -1;
	}
	return h;
}
