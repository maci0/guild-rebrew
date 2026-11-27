extern char g_7f4ca0[];
extern char g_868080[];
extern char gm_GameTime[];
extern char g_6a5e78[];
extern char g_6a5e60[];
extern char g_6a5e40[];
extern char g_6a5e24[];
extern char g_6a5e10[];
extern char g_6a5e00[];
extern char g_6a438c[];
extern char g_6a5de0[];
extern char g_6a5dcc[];
extern char g_6a5da8[];
extern char g_6a5d3c[];
extern char g_6a5d20[];
extern char g_6a5d04[];
extern char g_6a5ce8[];
extern char g_6a5ccc[];
extern char g_67d908[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_774964;
extern char g_7749e8;
extern int g_7749e4;
extern unsigned char g_773d75;
extern int g_100f884;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl gm_CompareGameTime(char*, char*);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl d2_CloseActionPopup(char*);
void __cdecl he_FreeAction(char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl io_AppendText(int, ...);

/* ADDRESS: GOLDTL 0x00554f00 */
void __cdecl he_RunTitleGrantEvent(char* obj)
{
	char* rec;
	char* h;
	char* p;
	char* s;
	char* name;
	unsigned short w;
	int st;
	unsigned char c;

	rec = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (obj + 8)]);
	if (g_774970 != *(unsigned short*) (obj + 8)) {
		return;
	}
	if (g_774964 == 0) {
		return;
	}
	name = obj + 0x52;
	if (gm_CompareGameTime(name, gm_GameTime) == 1) {
		return;
	}
	p = gm_LookupEntityRecordById(*(int*) (obj + 0xb0));
	st = *(int*) (obj + 0x70);
	if (st == -2 || st == -1 || *(unsigned short*) rec == 0xffff || p == 0) {
		if (*(int*) (obj + 0x74) != 0) {
			d2_CloseActionPopup(obj);
		}
		he_FreeAction(obj);
		return;
	}
	switch (st) {
	case 0: goto state_zero;
	case 1:
		h = *(char**) (obj + 0x74);
		if (h == 0) {
			*(int*) (obj + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (h + 8) && g_7749e8 == 0) {
			return;
		}
		if (g_100f1dc == 2) {
			d2_CloseActionPopup(obj);
			he_FreeAction(obj);
			return;
		}
		if (g_7749e8 == 0) {
			return;
		}
		if (g_7749e4 != (int) h) {
			return;
		}
		g_7749e8 = 0;
		d2_CloseActionPopup(obj);
		he_FreeAction(obj);
		return;
	default: return;
	}
state_zero:

	if (*(char**) (obj + 0x74) == 0) {
		d2_CreateActionPopupSlot(obj, 0, 0, (p == rec) ? g_6a5e78 : g_6a5e60, (p == rec) ? 0x5fd : 0x5fe);
	}

	if (*(char**) (obj + 0x74) == 0) {
		he_FreeAction(obj);
		return;
	}
	d2_CenterDialogWindows(*(int*) (*(char**) (obj + 0x74) + 8));
	d2_SetForm(*(int*) (*(char**) (obj + 0x74) + 8), 1);
	if (p == rec) {
	if (*(int*) (obj + 0xb4) == 0) {
		cm_BeginPacketFieldDelta(p, *(int*) (p + 4));
		cm_AppendPacketFieldDelta(1, 1, 0xd, obj + 0xac);
		cm_RequestChangeAttribute();
		*(int*) (obj + 0xb4) = 1;
	}
	c = *(unsigned char*) (obj + 0xac);
	if (c == 9) {
		io_AppendText(0x42a3, name);
	} else if (c == 8) {
		io_AppendText(0x42a1, name);
	} else if (c == 7) {
		io_AppendText(0x429f, name);
	} else if (c == 2) {
		io_AppendText(0x1618, g_868080 + g_773d75 * 0x2f4, name, *(unsigned short*) p, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x116);
	} else {
		io_AppendText(0x1617, g_868080 + g_773d75 * 0x2f4, name, *(unsigned short*) p, (int) c + ((*(char*) (p + 9) != 0) ? 0x11e : 0x114));
	}
	c = *(unsigned char*) (obj + 0xac);
	if (c == 2) {
		d3snd_QueueSound(-7, 0, g_6a5e40, 0, 0x64);
		d3snd_QueueSound(-8, 0, g_6a5e24, 0, 0xfa);
		d3snd_QueueSound(-8, 0, (*(char*) (p + 9) == 0) ? g_6a5e10 : g_6a5e00, (int) c, 0x64);
		d3snd_QueueSound(-7, 0, g_67d908, -1, 0);
		goto tail;
	}
	if (c <= 3) {
		s = g_6a5e40;
	} else if (c < 6) {
		s = g_6a5de0;
	} else {
		s = g_6a438c;
	}
	d3snd_QueueSound(-7, 0, s, 0, 0x64);
	if (c < 7) {
		d3snd_QueueSound(-8, 0, g_6a5dcc, 0, 0xfa);
		d3snd_QueueSound(-8, 0, (*(char*) (p + 9) == 0) ? g_6a5e10 : g_6a5e00, (int) c, 0x64);
	} else if (c == 7) {
		d3snd_QueueSound(-7, 0, g_6a5da8, -1, 0x64);
	} else if (c == 8) {
		d3snd_QueueSound(-7, 0, (char*) 0x6a5d84, -1, 0x64);
	} else if (c == 9) {
		d3snd_QueueSound(-7, 0, (char*) 0x6a5d60, -1, 0x64);
	}
	d3snd_QueueSound(-7, 0, g_67d908, -1, 0);
	goto tail;

	}
	c = *(unsigned char*) (obj + 0xac);
	w = *(unsigned short*) p;
	if (c == 9) {
		io_AppendText(0x42a4, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11d, (int) w);
	} else if (c == 8) {
		io_AppendText(0x42a2, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11c, (int) w);
	} else if (c == 7) {
		io_AppendText(0x42a0, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11b, (int) w);
	} else if (c == 2) {
		io_AppendText(0x161b, (int) w);
	} else {
		io_AppendText(0x161a, (int) w, (int) w, (int) c + ((*(char*) (p + 9) != 0) ? 0x11e : 0x114), (int) w);
	}
	c = *(unsigned char*) (obj + 0xac);
	if (c == 2) {
		d3snd_QueueSound(-8, 0, g_6a5d3c, 0, 0x64);
	} else if (c < 7) {
		d3snd_QueueSound(-8, 0, g_6a5d20, 0, 0x64);
		d3snd_QueueSound(-8, 0, (*(char*) (p + 9) == 0) ? g_6a5e10 : g_6a5e00, (int) c, 0x64);
	} else if (c == 7) {
		d3snd_QueueSound(-7, 0, g_6a5d04, -1, 0x64);
	} else if (c == 8) {
		d3snd_QueueSound(-7, 0, g_6a5ce8, -1, 0x64);
	} else if (c == 9) {
		d3snd_QueueSound(-7, 0, g_6a5ccc, -1, 0x64);
	}

tail:
	d2_SetForm(*(int*) (*(char**) (obj + 0x74) + 8), 2);
	io_AppendText(0x161c);
	*(int*) (obj + 0x70) = 1;
}
