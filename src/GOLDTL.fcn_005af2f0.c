


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	char pad60[0x10];
	int ids[4];
	char pad80[0x78];
} Packet;
// SIZE 0xf8

typedef struct
{
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_14abc98;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_7746c4;
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
void __cdecl fcn_005305a0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

int __cdecl fcn_005af2f0(int unused, char* a)
{
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;
	int btn2;

	if (a == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Player*)g_7f4ca0)[i].x188 != 0) {
			break;
		}
	}
	if (i >= 768) {
		fcn_00526120(g_14abc98, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6ab348);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x1a69);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				n = 0;
				memset(pkt.ids, 0xff, sizeof(pkt.ids));
				for (i = 0; i < 768; i++) {
					if (n >= 4) {
						break;
					}
					if (((Player*)g_7f4ca0)[i].x188 != 0) {
						pkt.ids[n] = ((Player*)g_7f4ca0)[i].x4;
						n++;
					}
				}
				if (n != 0) {
					pkt.type = 0x43;
					pkt.x36 = 2;
					pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
					pkt.x58 = *(int*) (a + 1);
					pkt.x5c = *(int*) (g_7746c4 + 1);
					for (; n < 4; n++) {
						pkt.ids[n] = -1;
					}
					fcn_004c5530(&pkt);
					cm_ExProdObjekt();
				}
				fcn_005305a0();
				g_774654 = 2;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005af2f0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
	return 1;
}
