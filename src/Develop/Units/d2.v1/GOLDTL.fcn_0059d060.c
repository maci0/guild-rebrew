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
extern char* g_7746c8;
extern int g_14abc44;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern Name14 g_7f4c00;
extern char s_6aa490[];

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005463a0(int, int, int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_004c35f0(void);
int __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl fcn_00529160(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x0059d060 */
int __cdecl fcn_0059d060(int unused, char* param)
{
	Packet pkt;
	char buf[0x400];
	int flag;
	int btn2;
	int btn1;
	int dlg;
	int dlg2;
	int count;
	int n;
	char* p;
	Player* player;
	Player* slot;

	flag = 0;
	dlg = fcn_00470820(0, 0, s_6aa490);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	n = io_AppendText(0x19ee, *(unsigned short*) (param + 0x27), param);
	btn1 = fcn_00472250(dlg, 1, n);
	btn2 = fcn_00472250(dlg, 1, n + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0)
			g_774654 = 1;
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				dlg2 = fcn_005463a0(3, 0, 0x49, 2,
					*(unsigned short*) (g_7746c8 + 0x27), 3,
					*(int*) (g_7746c8 + 1));
				while (dlg2 != 0) {
					if (*(int*) (dlg2 + 0xac) == *(int*) (param + 1))
						break;
					dlg2 = he_fn_Handlung();
				}
				if (dlg2 == 0) {
					pkt.type = 0x49;
					slot = &((Player*) g_7f4ca0)[*(unsigned short*) (g_7746c8 + 0x27)];
					pkt.x8 = slot->x4;
					pkt.xc = *(int*) (g_7746c8 + 1);
					pkt.name = g_7f4c00;
					pkt.x36 = 1;
					pkt.x58 = *(int*) (param + 1);
					pkt.x5c = *(int*) (g_7746c8 + 1);
					for (n = 0; n < 8; n++)
						pkt.ids[n] = -1;
					n = 0;
					for (p = (char*) 0x7e4260; (int) p < 0x7e42e0; p += 4) {
						if (n >= 6)
							break;
						player = *(Player**) p;
						if (player != 0 && player->x188 != 0) {
							pkt.ids[n] = player->x4;
							n++;
						}
					}
					if (n == 0) {
						fcn_00526120(g_14abc44, 0);
					}
					else {
						flag = 1;
						fcn_004c5530(&pkt);
						fcn_004c35f0();
						count = 0;
						for (p = (char*) 0x7e4260; (int) p < 0x7e42e0; p += 4) {
							player = *(Player**) p;
							if (player != 0 && player->x188 != 0)
								count++;
						}
						if (count > 6) {
							io_FormatTextBuffer(buf, 0x19ef, 6);
							fcn_00526120((int) buf, 0);
						}
						g_774654 = 2;
					}
				}
				else {
					flag = 1;
					g_774654 = 2;
					for (p = (char*) 0x7e4260; (int) p < 0x7e42e0; p += 4) {
						player = *(Player**) p;
						if (player != 0 && player->x188 != 0)
							fcn_00529160(0, 0, *(unsigned short*) player, dlg2);
					}
				}
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
		if (fcn_005373e0((void*) fcn_0059d060, 0x677c7) == 0) {
			fcn_00471e30(dlg);
			return flag;
		}
	} while (1);
}
