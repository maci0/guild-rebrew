


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
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_14abd04;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern unsigned char* g_7746c8;
extern char s_6aa4e8[];

int __cdecl fcn_0055c050(char*);
void __cdecl io_FormatTextBuffer(char*, int, unsigned short, char*);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_005100f0(int, int);
void __cdecl cm_ExProdObjekt(void);
void __cdecl fcn_0052ae70(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_0059da50(int unused, char* e)
{
	int btn1;
	Packet pkt;
	char buf[0x400];
	int dlg;
	int s;
	int btn2;
	int n;
	int i;

	if (e == 0 || *(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	if (fcn_0055c050(e) == 0) {
		io_FormatTextBuffer(buf, 0x1a92, *(unsigned short*) (e + 0x27), e);
		fcn_00526120(buf, 0);
		return;
	}
	dlg = fcn_00470820(0, 0, s_6aa4e8);
	fcn_00471b60(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a84, e);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				pkt.type = 0x75;
				pkt.x36 = 1;
				n = 0;
				pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
				pkt.x58 = *(int*) (e + 1);
				pkt.x5c = *(int*) (((char*)g_7746c8) + 1);
				for (i = 0; i < 8; i++) {
					pkt.ids[i] = -1;
				}
				for (i = 0; i < 768; i++) {
					if (((Player*)g_7f4ca0)[i].x188 != 0) {
						pkt.ids[n] = ((Player*)g_7f4ca0)[i].x4;
						n++;
					}
				}
				if (n != 0) {
					fcn_004c5530(&pkt);
					fcn_005100f0(((Player*)g_7f4ca0)[g_774970].x4, -1);
					cm_ExProdObjekt();
				}
				else {
					fcn_00526120((char*) g_14abd04, 0);
				}
				g_774654 = 1;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0059da50, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_0052ae70();
}
