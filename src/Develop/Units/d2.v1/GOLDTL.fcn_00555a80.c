/* panel/slot record edited by this handler */
typedef struct {
	char p0[8];
	unsigned short id;
	char pa[0x48];
	char name[0x1a];
	char p6c[4];
	int state;
	char* handle;
	char p78[0x34];
	unsigned char kind;
	char paf[1];
	int sub;
	int base;
} Panel;

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_774964;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_100f884;
extern char g_7749e8;
extern int g_7749e4;
extern int g_100f1dc;

int __cdecl gm_CompareGameTime(char* name, char* list);
void __cdecl fcn_00545780(Panel* p);
void __cdecl he_FreeAction(Panel* p);
void __cdecl fcn_00545670(Panel* p, int a1, int a2, char* fmt, int a4);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a1);
void __cdecl io_AppendText(int a0);
void __cdecl d3snd_QueueSound(int a0, int a1, char* fmt, int a3, int a4);

/* ADDRESS: GOLDTL 0x00555a80 */
void __cdecl d2_HandleTalentLevelDialog(Panel* p)
{
	ENTITY_RECORD* rec;
	int id;
	int v;

	id = (int) p->id;
	rec = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[id]);
	if (g_774970 != p->id) {
		return;
	}
	if (g_774964 == 0) {
		return;
	}
	if (gm_CompareGameTime(p->name, (char*) 0x7f4c00) == 1) {
		return;
	}
	if (p->state == -2 || p->state == -1) {
		goto update;
	}
	if (rec->entity_index == 0xffff) {
		goto update;
	}
	switch (p->state) {
	case 0:
		goto open;
	case 1:
		break;
	default:
		return;
	}
	if (p->handle == 0) {
		p->state = 0;
		return;
	}
	if ((g_100f884 != *(int*) (p->handle + 8) && g_7749e8 == 0) && g_100f1dc == -1) {
		return;
	}
	if (g_100f1dc == 2) {
		fcn_00545780(p);
		he_FreeAction(p);
		return;
	}
	if (g_7749e8 == 0) {
		return;
	}
	if (g_7749e4 != (int) p->handle) {
		return;
	}
	g_7749e8 = 0;
	fcn_00545780(p);
	he_FreeAction(p);
	return;
open:
	if (p->handle == 0) {
		fcn_00545670(p, 0, 0, (char*) 0x6a5ec4, 0x5ec);
	}
	if (p->handle == 0) {
		he_FreeAction(p);
		return;
	}
	d2_CenterDialogWindows(*(int*) (p->handle + 8));
	d2_SetForm(*(int*) (p->handle + 8), 1);
	io_AppendText(0x16c8);
	v = p->base + (int) p->kind * 6 + 0x16c9;
	io_AppendText(v);
	d3snd_QueueSound(-7, 0, (char*) 0x6a5e40, 0, 0x64);
	d3snd_QueueSound(-8, 0, (char*) 0x6a5eb4, p->base + (int) p->kind * 6, 0xfa);
	if (p->sub < 6) {
		io_AppendText(p->sub + 0x16e6);
		d3snd_QueueSound(-8, 0, (char*) 0x6a5ea4, p->sub - 1, 0x64);
	} else {
		io_AppendText((int) p->kind + 0x16ec);
		d3snd_QueueSound(-8, 0, (char*) 0x6a5e98, (int) p->kind, 0x64);
	}
	d3snd_QueueSound(-7, 0, (char*) 0x67d908, -1, 0);
	d2_SetForm(*(int*) (p->handle + 8), 2);
	io_AppendText(0x16f1);
	p->state = 1;
	return;
update:
	if (p->handle != 0) {
		fcn_00545780(p);
	}
	he_FreeAction(p);
}
