// FUNCTION: GOLDTL 0x005ad380
// SIZE: 542

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

typedef struct
{
	unsigned short x0;
	char pad2[2];
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern Player g_7f4ca0[];
extern unsigned short g_774970;
extern char* g_7746c4;
extern int g_14abab4;
extern int g_14abaac;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6aa464[];

int __cdecl fcn_0055c050(char*);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_0050c550(char*, char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005ad380(int unused, char* e)
{
	int r;
	int btn1;
	Packet pkt;
	char buf[0x400];
	Player* p;
	int dlg;
	int s;
	int btn2;
	int n;
	int i;

	r = 0;
	if (e == 0) {
		return 0;
	}
	p = &g_7f4ca0[*(unsigned short*) (e + 0x27)];
	if (fcn_0055c050(e) == 0) {
		fcn_0051af00(buf, 0x1a92, *(unsigned short*) (e + 0x27), e);
		fcn_00526120(buf, 0);
		return 0;
	}
	if (fcn_0050c550(g_7746c4, e) == 0) {
		fcn_00526120((char*) g_14abab4, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6aa464);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x19e4, p->x0, e);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				pkt.type = 0x3f;
				pkt.x36 = 1;
				n = 0;
				pkt.x8 = g_7f4ca0[g_774970].x4;
				pkt.x58 = *(int*) (e + 1);
				pkt.x5c = *(int*) (g_7746c4 + 1);
				for (i = 0; i < 8; i++) {
					pkt.ids[i] = -1;
				}
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i].x188 != 0) {
						pkt.ids[n] = g_7f4ca0[i].x4;
						n++;
					}
				}
				if (n != 0) {
					fcn_004c5530(&pkt);
					cm_ExProdObjekt();
				}
				else {
					fcn_00526120((char*) g_14abaac, 0);
				}
				fcn_005305a0();
				g_774654 = 1;
				r = 1;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005ad380, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
