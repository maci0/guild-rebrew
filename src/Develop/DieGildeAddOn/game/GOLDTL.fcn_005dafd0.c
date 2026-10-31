


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[15];
} Req;

// SIZE 0x18
typedef struct {
	int f0;
	char pad4[0x14];
} Info;

extern __int64 g_666018;
extern unsigned short g_7f4c04;
extern char* g_14acb58;
extern int g_14ac6a0;
extern char s_6acd74[];
extern char s_6ace58[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004e8a80(int, Info*);
#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00526120(char*, int);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(unsigned char*, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dafd0(unsigned char* e, unsigned char* a2)
{
	int result;
	int cancel;
	int ok;
	Info info;
	Req req;
	char text[0x200];
	unsigned char* o;
	int dlg;
	int id;
	int h;

	if (e[2] != 6) {
		if (*(int*) (e + 0x1cc) & 0x40000) {
			return 0x20;
		}
		if (*(int*) (e + 0x194) < 8) {
			return 0x20;
		}
		o = gm_LookupEntityRecordById(*(int*) (a2 + 0x214));
		if (o == 0) {
			return 0x60;
		}
		if (o[0x166] == 0) {
			return 0x60;
		}
		if (!fcn_004e8a80(o[0x166], &info)) {
			return 0x40;
		}
		fcn_004e8240(info.f0, 0, 0, g_7f4c04 > 0xd ? 0xff : 3, 0xff);
		fcn_005100f0(*(int*) (e + 4), -8);
		fcn_004c5420(*(int*) (e + 4), 0x1cc, 4, 0x40000, 0);
		if (o[2] == 6 || o[2] == 7) {
			io_FormatTextBuffer(text, 0x1e10, *(unsigned short*) e, o[9] == 0 ? 0x253 : o[0x166] + 0x27b);
			fcn_00545d40(*(int*) (o + 4), -1, text, 0, 0x5fb, s_6ace58);
		}
		return 0x10;
	}
	result = 2;
	memset(&req, 0, sizeof(req));
	if (*(int*) (e + 0x1cc) & 0x40000) {
		fcn_00526120(((char*)g_14ac6a0), 0);
		return 0x81;
	}
	req.size = 0xc00;
	req.kind = 6;
	req.cd = g_666018;
	o = fcn_005cd440(&req, g_14acb58, 0, 0);
	if (o == 0) {
		return 2;
	}
	if (!fcn_004e8a80(o[0x166], &info)) {
		return 0x40;
	}
	dlg = fcn_00470820(0, 0, s_6acd74);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1e0f, *(unsigned short*) o);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok && fcn_00525f60(e, 8)) {
				fcn_004e8240(info.f0, 0, 0, g_7f4c04 > 0xd ? 0xff : 3, 0xff);
				fcn_005100f0(*(int*) (e + 4), -8);
				h = fcn_004c5420(*(int*) (e + 4), 0x1cc, 4, 0x40000, 0);
				while (h != -1 && fcn_004c4450(h) == 0) {
					fcn_00535960();
				}
				g_774654 = 1;
				result = 0x91;
				if (o[2] == 6 || o[2] == 7) {
					io_FormatTextBuffer(text, 0x1e10, *(unsigned short*) e, o[9] == 0 ? 0x253 : o[0x166] + 0x27b);
					fcn_00545d40(*(int*) (o + 4), -1, text, 0, 0x5fb, 0);
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005dafd0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
