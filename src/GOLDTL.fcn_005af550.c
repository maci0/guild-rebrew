typedef struct {
	char b[14];
} Name14;
// SIZE 0xe

typedef struct {
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

typedef struct {
	char pad0[4];
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char* g_7746c4;
extern int g_14abc98;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ab348[];

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl fcn_0051af00(char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005af550 */
int __cdecl fcn_005af550(int unused, char* param)
{
	Packet pkt;
	char buf[0x400];
	int flag;
	int btn;
	int btn1;
	int btn2;
	int dlg;
	int i;
	int n;
	int count;
	char* p;

	flag = 0;
	if (param == 0)
		return 0;
	i = 0;
	p = g_7f4ca0 + 0x188;
	while (p < (char*) 0x85a228) {
		if (*p != 0)
			break;
		p += 0x21c;
		i++;
	}
	if (p >= (char*) 0x85a228 || i >= 0x300) {
		fcn_00526120(g_14abc98, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6ab348);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	btn = fcn_00519190(0x1a6d, param);
	btn1 = fcn_00472250(dlg, 1, btn);
	btn2 = fcn_00472250(dlg, 1, btn + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0)
			g_774654 = 1;
		if (g_100f1dc != -1) {
			if (g_67d370 != btn1) {
				if (g_67d370 == btn2)
					g_774654 = 1;
			} else {
				for (i = 0; i < 8; i++)
					pkt.ids[i] = -1;
				n = 0;
				for (p = g_7f4ca0 + 4; p < (char*) 0x85a0a4; p += 0x21c) {
					if (n >= 6)
						break;
					if (*(unsigned char*) (p + 0x184)) {
						pkt.ids[n] = *(int*) p;
						n++;
					}
				}
				if (n != 0) {
					pkt.type = 0x44;
					pkt.x8 = ((Player*) g_7f4ca0)[g_774970].x4;
					pkt.x36 = 2;
					pkt.x58 = *(int*) (param + 1);
					pkt.x60 = *(int*) (g_7746c4 + 1);
					fcn_004c5530(&pkt);
					cm_ExProdObjekt();
					flag = 1;
					count = 0;
					for (p = g_7f4ca0 + 0x188; p < (char*) 0x85a228; p += 0x21c) {
						if (*p)
							count++;
					}
					if (count >= 7) {
						fcn_0051af00(buf, 0x19ef, 6);
						fcn_00526120(buf, 0);
					}
				}
				g_774654 = 2;
			}
		}
		if (!fcn_005373e0((void*) fcn_005af550, 0x677c7)) {
			fcn_00471e30(dlg);
			return flag;
		}
	} while (1);
}
