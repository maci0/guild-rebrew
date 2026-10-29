typedef struct {
	int v[0x11];
} Rec44_58ee70;

typedef struct {
	int kind;
	int cost;
	int f8;
	unsigned char fc;
	char padd[3];
	int f10;
	Rec44_58ee70 rec;
} Result_58ee70;

typedef struct {
	int dlg;
	int w1;
	int w2;
	int w3;
	int w4;
	int w5;
	int w6;
	char* rec;
	int rec_id;
	unsigned char rec_state;
	char pad25[3];
	char entries[0x60];
	int selected;
} Dialog_58ee70;

extern unsigned short g_774970;
#include "GOLDTL.fcn_0058ee70_gconf.h"
extern int g_14b5650;
extern int g_14b5674;
extern int g_665f78[];

void* __cdecl FindSlotEntryFiltered(int, char*, unsigned char*, void*, int);
int __cdecl fcn_004f1790(int, void*);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_0058c410(int*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_0058edc0(int, char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_0058e510(char*, char*);
void __cdecl fcn_0058ea60(char*, char*);
void __cdecl fcn_0058e790(char*, char*);
void __cdecl fcn_00526120(int, int);

/* ADDRESS: GOLDTL 0x0058ee70 */
void __cdecl fcn_0058ee70(char* e)
{
	Result_58ee70 result;
	Dialog_58ee70 dlg;
	unsigned char text[0xf8];
	unsigned char* rec;
	int r;
	unsigned char v;

	rec = FindSlotEntryFiltered((int) (g_slot_table + g_774970 * 0x21c), e, 0, (void*) 0x4f1820, 0xff);
	if (rec == 0) {
		fcn_00526120(g_14b5674, 0);
		return;
	}
	v = (unsigned char) fcn_004f1790(*(int*) (e + 0x65), rec);
	dlg.rec = (char*) rec;
	dlg.rec_id = *(int*) rec;
	dlg.rec_state = v;
	fcn_0051af00(text, 0x4107, g_665f78[*(int*) rec]);
	if (!fcn_0058c410((int*) &dlg, g_14b5650)) {
		fcn_00532ef0();
		return;
	}
	r = fcn_0058edc0((int) e, (char*) &dlg, (int) &result);
	fcn_00471e30(dlg.dlg);
	if (r != 0) {
		fcn_004c5420(*(int*) (g_slot_table + g_774970 * 0x21c + 4), 0x1cc, 4, 0x800000, 0);
		if (result.rec.v[1] != 0) {
			fcn_005100f0(*(int*) (g_slot_table + g_774970 * 0x21c + 4), -result.rec.v[1]);
		}
		switch (result.kind) {
		case 1:
			fcn_0058e510(e, (char*) &result);
			break;
		case 2:
			fcn_0058ea60(e, (char*) &result);
			break;
		case 3:
			fcn_0058e790(e, (char*) &result);
			break;
		}
	}
	fcn_00532ef0();
}
