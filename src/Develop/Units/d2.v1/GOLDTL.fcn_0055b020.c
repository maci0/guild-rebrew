#include <string.h>
#pragma intrinsic(strcpy)

extern char g_7f4ca0[];
extern char g_774964;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
extern int g_100f884;
extern char g_7749e8;
extern int g_7749e4;

int __cdecl fcn_00545670(char*, short, short, char*, int);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00500cb0(void*, void*);

/* ADDRESS: GOLDTL 0x0055b020 */
void __cdecl fcn_0055b020(char* o)
{
	short* slot;
	char* g;
	char buf[0x1fc];
	int state;
	int st;
	int code;
	int kind;
	int end;
	int id;

	slot = (short*) (g_7f4ca0 + *(unsigned short*) (o + 8) * 0x21c);
	if (g_774970 != *(unsigned short*) (o + 8))
		return;
	if (g_774964 == 0)
		return;
	if (fcn_00500cb0(o + 0x52, (void*) 0x7f4c00) == 1)
		return;
	g = gm_LookupEntityRecordById(*(int*) (o + 0xbc));
	state = *(int*) (o + 0x70);
	if (state == -2 || state == -1 || *slot == -1 || g == 0) {
		if (*(int*) (o + 0x74))
			fcn_00545780(o);
		fcn_00546190(o);
		return;
	}
	if (state != 0) {
		if (state != 1)
			return;
		id = *(int*) (o + 0x74);
		if (id == 0) {
			*(int*) (o + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (id + 8) && g_7749e8 == 0)
			return;
		if (g_100f1dc == 2) {
			fcn_00545780(o);
			fcn_00546190(o);
			return;
		}
		if (g_7749e8 == 0)
			return;
		if (g_7749e4 != id)
			return;
		g_7749e8 = 0;
		fcn_00545780(o);
		fcn_00546190(o);
		return;
	}
	if (*(int*) (o + 0x74) == 0) {
		if (g == (char*) slot)
			fcn_00545670(o, 0, 0, "SPECIAL\\TITEL", 0x5fd);
		else
			fcn_00545670(o, 0, 0, "SPECIAL\\TITEL_ANDERE", 0x5fe);
	}
	if (*(int*) (o + 0x74) == 0) {
		fcn_00546190(o);
		return;
	}
	fcn_00471b60(*(int*) (*(int*) (o + 0x74) + 8));
	d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 1);
	if (g == (char*) slot) {
		kind = 0;
		if (*(char*) (g + 0xd) == 9) {
			code = 0x42a9;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_02");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_02");
		} else if (*(char*) (g + 0xd) == 8) {
			code = 0x42a7;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_01");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_01");
		} else {
			code = 0x42a5;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_00");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_00");
		}
		if (*(char*) (g + 9) == 1)
			code += 1;
		fcn_004c30a0(-7, 0, "FanfarePositivHeldenhaftLang", 0, 100);
		fcn_004c30a0(-7, 0, buf, 0, 100);
		if (*(int*) (o + 0xc0) == 0x25) {
			kind = 0x42ab;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_00");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_00");
		} else if (*(int*) (o + 0xc0) == 0x24) {
			kind = 0x42af;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_02");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_02");
		} else if (*(int*) (o + 0xc0) == 0x23) {
			kind = 0x42ad;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_01");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_01");
		}
		fcn_004c30a0(-7, 0, buf, 0, 100);
		fcn_004c30a0(-7, 0, "MausclickLinks_s_01", -1, 0);
		if (*(char*) (g + 9))
			end = *(int*) (o + 0xc0) + 0x27b;
		else
			end = 0x253;
		io_AppendText(kind, code, (int) (o + 0xac), end);
	} else {
		st = *(int*) (o + 0xc0);
		kind = 0;
		if (st == 0x25)
			kind = 0x42ac;
		else if (st == 0x24)
			kind = 0x42b0;
		else if (st == 0x23)
			kind = 0x42ae;
		if (*(char*) (g + 9))
			end = st + 0x27b;
		else
			end = 0x253;
		io_AppendText(kind, *(unsigned short*) g, end);
	}
	d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 2);
	io_AppendText(0x161c);
	*(int*) (o + 0x70) = 1;
}
