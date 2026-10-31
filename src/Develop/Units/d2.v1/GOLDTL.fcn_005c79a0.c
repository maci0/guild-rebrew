void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	char b[14];
} Name14;
/* SIZE 0xe */

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
/* SIZE 0xf8 */

typedef struct
{
	unsigned char x0;
	char pad1[0x24c];
} Shop;
/* SIZE 0x24d */

typedef struct
{
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
/* SIZE 0x21c */

extern unsigned char* lpGebaeudePROT;
extern char* g_77255c;
extern int g_772514;
extern int g_6b7fac;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_14abc44;
extern int g_774654;
extern int g_7746c0;
extern char* g_7746cc;
extern int g_7746f0;
extern unsigned short g_774970;
extern int g_7ea360;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern char s_6aa194[];
extern char s_6ac79c[];
extern char s_6ac7dc[];
extern char s_6ac7ec[];
extern char s_6ac7fc[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl d2_SetBackgroundTexture(const char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl CountDisplayCounters(void);
void __cdecl fcn_004c35f0(void);
int __cdecl fcn_004c5530(Packet*);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl io_AppendText(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_0052a0c0(unsigned char*, int);
void __cdecl fcn_0052a2d0(void);
int __cdecl fcn_0052ae70(void);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_005c78f0(int, int, int*, int);

/* ADDRESS: GOLDTL 0x005c79a0 */
void __cdecl fcn_005c79a0(unsigned char* obj)
{
	char buf[0x800];
	Packet pkt;
	int out1[3];
	int out2[3];
	int out3[3];
	int btnA;
	int btnB;
	int btnC;
	int dlg;
	int start;
	int cnt2;
	int cnt3;
	int cnt6c;
	int sum;
	int i;
	int hwnd;
	Shop* t;
	Player* pl;
	unsigned int* q;
	char* p;
	unsigned char* e;

	btnC = 0;
	t = &((Shop*) lpGebaeudePROT)[obj[0]];
	dlg = fcn_00470820(0, 0, s_6ac79c);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_00533dc0(g_772514, 0x72f, 0);
	d2_SetForm(dlg, 3);
	io_AppendText(0x1a46);
	fcn_0052a0c0(obj, 1);
	d2_SetForm(dlg, 2);
	hwnd = g_772514;
	fcn_005c78f0(0, 0x762, out1, hwnd);
	fcn_005c78f0(1, 0x763, out2, hwnd);
	fcn_005c78f0(2, 0x764, out3, hwnd);
	d2_SetForm(out1[0], 1);
	if (t->x0 != 4 && t->x0 != 0x10) {
		d2_SetBackgroundTexture(s_6ac7fc, *(int*) g_77255c);
	}
	else {
		d2_SetBackgroundTexture(s_6ac7ec, *(int*) g_77255c);
	}
	start = g_6b7fac;
	*(int*) (g_77255c + 0x3a4) = 0;
	btnA = fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x35);
	btnB = fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x34);
	if (t->x0 == 4) {
		btnC = fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x5d) != 0;
	}
	else if (t->x0 == 0x10) {
		btnC = fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x5e) != 0;
	}
	fcn_00472640(out1[0], btnA != 0);
	fcn_00472640(out2[0], btnB != 0);
	fcn_00472640(out3[0], btnC);
	for (;;) {
		d2_SetForm(dlg, 1);
		i = g_6b7fac - start;
		*(float*) (g_77255c + 0x3a4) = (float) ((double) i * 0.0013333333333333333);
		if (*(float*) (g_77255c + 0x3a4) > 0.4f) {
			*(float*) (g_77255c + 0x3a4) = 0.4f;
		}
		if (g_14ce8e0 != 0) {
			if (CountDisplayCounters() != 0) {
				fcn_0052ae70();
			}
			else {
				g_774654 = 1;
			}
		}
		cnt2 = 0;
		cnt3 = 0;
		sum = 0;
		p = fcn_005463a0(2, 0, 0x16, 3, *(int*) (obj + 1));
		if (p != 0) {
			while (p != 0) {
				if (*(char*) (p + 0xac) == 2) {
					cnt2++;
				}
				else if (*(char*) (p + 0xac) == 3) {
					cnt3++;
				}
				p = he_fn_Handlung();
			}
			cnt2 = cnt2;
			cnt3 = cnt3;
		}
		cnt6c = 0;
		p = fcn_005463a0(2, 0, 0x6c, 3, *(int*) (obj + 1));
		while (p != 0) {
			cnt6c++;
			p = he_fn_Handlung();
		}
		hwnd = g_772514;
		g_772514 = hwnd;
		io_AppendText(s_6aa194, cnt2, 0x51e, 0x1a47, 0x16b9);
		g_772514 = hwnd;
		io_AppendText(s_6aa194, cnt3, 0x51e, 0x1a47, 0x16ba);
		g_772514 = hwnd;
		io_AppendText(s_6ac7dc, cnt6c, 0x51e, 0x1a48);
		if (g_100f1dc != -1) {
			if (CountDisplayCounters() != 0) {
				i = 0;
				do {
					if (out1[i * 3] != -1 && g_67d370 == out1[i * 3]) {
						sum = cnt3 + cnt2;
						if (i == 0 || i == 1) {
							q = (unsigned int*) 0x7f4e1c;
							do {
								if (*(char*) ((char*) q + 0xc) != 0) {
									memset(&pkt, 0, sizeof(pkt));
									if (*(char*) *q != 0 && *(char*) *q == 0x16) {
										sum--;
									}
									if (sum >= 3) {
										sum = 4;
										goto send;
									}
									pkt.type = 0x16;
									pkt.x8 = *(int*) g_7f4ca4;
									pkt.xc = *(int*) (obj + 1);
									pkt.name = *(Name14*) &g_7f4c00;
									pkt.x36 = 1;
									if (g_7746cc != 0) {
										pkt.x60 = *(int*) (g_7746cc + 2);
									}
									else {
										pkt.x60 = -1;
									}
									*(char*) &pkt.x58 = (char) (i + 2);
									pkt.x5c = *(int*) g_7f4ca4;
									fcn_00529160(obj, 0, *(unsigned short*) g_7f4ca0, 0);
									fcn_004c5530(&pkt);
									sum++;
								}
								q += 0x87;
							} while ((int) q < 0x85a21c);
						}
						else {
							pl = (Player*) g_7f4ca4;
							do {
								if (sum >= 3) {
									break;
								}
								if (*(char*) ((char*) pl + 0x184) != 0) {
									memset(&pkt, 0, sizeof(pkt));
									pkt.type = 0x6c;
									pkt.x8 = *(int*) ((char*) g_7f4ca4 + *(unsigned short*) (obj + 0x27) * 0x21c);
									pkt.xc = *(int*) (obj + 1);
									pkt.name = *(Name14*) &g_7f4c00;
									pkt.x36 = 1;
									if (g_7746cc != 0 && *(unsigned short*) g_7746cc != 0xfd) {
										pkt.x60 = *(int*) (g_7746cc + 2);
									}
									else {
										pkt.x60 = -1;
									}
									pkt.x58 = *(int*) ((char*) pl);
									fcn_00529160(obj, 0, *(unsigned short*) ((char*) pl - 4), 0);
									fcn_004c5530(&pkt);
									sum++;
								}
								pl++;
							} while ((int) pl < 0x85a0a4);
						}
						if (sum != 0) {
send:
							fcn_004c35f0();
							fcn_0052ae70();
							if (sum >= 4) {
								io_FormatTextBuffer(buf, 0x1a4a, 3);
								fcn_00526120(buf, 0);
							}
							break;
						}
						fcn_00526120((char*) g_14abc44, 0);
					}
					i++;
				} while (i < 3);
			}
			else {
				i = 0;
				do {
					if (out1[i * 3] != -1 && g_67d370 == out1[i * 3]) {
						if (i != 2) {
							for (p = fcn_005463a0(2, 0, 0x16, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
								if (*(char*) (p + 0xac) == (char) (i + 2)) {
									e = gm_LookupEntityRecordById(*(int*) (p + 0xb0));
									if (e != 0) {
										*(char*) (e + 0x188) = 1;
									}
								}
							}
						}
						else {
							for (p = fcn_005463a0(2, 0, 0x6c, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
								e = gm_LookupEntityRecordById(*(int*) (p + 0xac));
								if (e != 0) {
									*(char*) (e + 0x188) = 1;
								}
							}
						}
						break;
					}
					i++;
				} while (i < 3);
			}
		}
		if (fcn_005373e0((void*) fcn_005c79a0, 0x677c7) == 0) {
			fcn_0052a2d0();
			fcn_00471e30(dlg);
			fcn_00532ef0();
			g_7ea360 = 0;
			g_7746c0 = 0;
			for (p = (char*) 0x7f4e28; (int) p < 0x85a228; p += 0x21c) {
				*p = 0;
			}
			g_7746f0 = 0;
			return;
		}
	}
}
