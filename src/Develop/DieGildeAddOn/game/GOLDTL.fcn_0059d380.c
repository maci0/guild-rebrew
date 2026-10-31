#include <string.h>

#include "client_types.h"

/* SIZE 0xf8 */
typedef struct {
	int f0;			/* +0x00 */
	unsigned char b4;	/* +0x04 */
	char pad5[3];
	int f8;			/* +0x08 */
	int fc;			/* +0x0c */
	char pad10[0x18];
	pos14_7f4c00 pos28;	/* +0x28 */
	unsigned char b36;	/* +0x36 */
	char pad37[0x21];
	int f58;		/* +0x58 */
	int f5c;		/* +0x5c */
	char pad60[8];
	int f68;		/* +0x68 */
	int f6c;		/* +0x6c */
	char pad70[0x88];
} Msg_59d380;

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_774970;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern char* g_7746a4;
extern int g_14abd04;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6aa4b8[];

extern char* __cdecl fcn_005463a0(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern int __cdecl fcn_0055c050(char*);
extern void __cdecl io_FormatTextBuffer(char*, char*, ...);
extern int __cdecl fcn_00526120(char*, int);
extern int __cdecl fcn_00470820(int, int, char*);
extern void __cdecl fcn_00471b60(int);
extern void __cdecl d2_SetOverlayAnimation(int, int);
extern void __cdecl d2_SetForm(int, int);
extern int __cdecl io_AppendText(int, ...);
extern int __cdecl fcn_00472250(int, int, int);
extern void __cdecl fcn_004c35f0(void);
extern void __cdecl fcn_004c5530(Msg_59d380*);
extern void __cdecl fcn_0052ae70(void);
extern int __cdecl fcn_005373e0(void*, int);
extern void __cdecl fcn_00471e30(int);


/* Oeffnet den Jahrmarkt-Dialog eines Objekts, bietet seine zwei Eintraege an
 * und schickt beim Anklicken das Nachrichtenpaket 0x62. */
/* ADDRESS: GOLDTL 0x0059d380 */
int __cdecl fcn_0059d380(char* a1)
{
	Msg_59d380 m;
	char buf[512];
	char* e;
	char** obj;
	int i;
	int dlg;
	int item1;
	int item2;
	int slot;

	if (a1 == 0) {
		return 0;
	}
	e = fcn_005463a0(1, 0, 0x62);
	while (e != 0) {
		if (*(int*) (e + 0xb0) == *(int*) (a1 + 1)) {
			io_FormatTextBuffer(buf, (char*) 0x1a91, *(unsigned short*) (a1 + 0x27), a1);
			fcn_00526120(buf, 0);
			return 0;
		}
		e = he_fn_Handlung();
	}
	for (i = 0; i < 0x300; i++) {
		if (*(char*) (g_7f4ca0 + i * 0x21c + 0x188) != 0) {
			break;
		}
	}
	if (i >= 0x300) {
		fcn_00526120((char*) g_14abd04, 0);
		return 0;
	}
	if (fcn_0055c050(a1) == 0) {
		io_FormatTextBuffer(buf, (char*) 0x1a89, *(unsigned short*) (a1 + 0x27), a1);
		fcn_00526120(buf, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6aa4b8);
	fcn_00471b60(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	item1 = io_AppendText(0x1a8b, a1);
	item2 = fcn_00472250(dlg, 1, item1);
	fcn_00472250(dlg, 1, item1 + 1);
	g_100f1dc = -1;
	while (fcn_005373e0((void*) fcn_0059d380, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == -1) {
			continue;
		}
		if (g_67d370 != item1) {
			if (g_67d370 == item2) {
				g_774654 = 1;
			}
			continue;
		}
		fcn_004c35f0();
		m.b4 = 0x62;
		slot = g_774970 * 0x21c;
		m.f8 = *(int*) (g_7f4ca0 + slot + 4);
		if (g_7746c4 != 0) {
			m.fc = *(int*) (g_7746c4 + 1);
		} else {
			m.fc = *(int*) (g_7746c8 + 1);
		}
		m.pos28 = g_7f4c00;
		m.b36 = 2;
		m.f5c = *(int*) (a1 + 1);
		if (g_7746c4 != 0) {
			m.f68 = *(int*) (g_7746c4 + 1);
		} else {
			m.f68 = *(int*) (g_7746c8 + 1);
		}
		if (g_7746cc != 0) {
			m.f6c = *(int*) (g_7746cc + 2);
		} else {
			m.f6c = -1;
		}
		obj = (char**) 0x7e4260;
		for (i = 0; i < 0x20; i++) {
			e = obj[i];
			if (e != 0 && *(char*) (e + 0x188) != 0) {
				m.f58 = *(int*) (e + 4);
				break;
			}
		}
		fcn_004c5530(&m);
		g_774654 = 1;
		fcn_0052ae70();
	}
	fcn_00471e30(dlg);
	return 0;
}
