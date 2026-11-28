#include "Develop/DieGildeAddOn/game/spiel.h"



// SIZE 0x10
struct offer {
	int id;
	int pad4;
	int kind;
	float val;
};

// SIZE 0x38
struct deal {
	int state;
	int pad4;
	struct offer e[3];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








extern char d2_KanoneHitTable[];
extern char* gm_CityEntity;
extern int g_774a1c;
extern volatile int gm_GameTicks;

void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetFormVisibility(int, int);

int __cdecl io_AppendText(int, ...);

void __cdecl d2_UpdateDealSummaryLog(char* w)
{
	int i;
	int cnt;
	char* o;
	int j;
	int msg;

	cnt = 0;
	if (*(unsigned int*) (w + 0x70) + 0x15e > gm_GameTicks) {
		return;
	}
	*(unsigned int*) (w + 0x70) = gm_GameTicks;
	d2_SetForm(*(int*) (w + 0x74), 0);
	for (i = 0; i < 3; i++) {
		if (((struct deal*)d2_KanoneHitTable)[i].state != i) {
			continue;
		}
		g_774a1c = 1;
		for (j = 0; j < 3; j++) {
			gm_ResolveEntityById((void**) (&o), 0, 0, ((struct deal*)d2_KanoneHitTable)[i].e[j].id);
			if (o == 0) {
				break;
			}
			msg = 0x4071;
			if (((struct deal*)d2_KanoneHitTable)[i].e[j].kind == 1) {
				msg = 0x4073;
				if (!(((struct deal*)d2_KanoneHitTable)[i].e[j].val > 25.0f)) {
					msg = 0x4072;
				}
			}
			if (j != 0) {
				io_AppendText((int) "$A");
			} else {
				io_AppendText((int) "$C");
			}
			if (*(unsigned short*) (o + 0x27) != 0xffff && &((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (o + 0x27)] != ((ENTITY_RECORD*)gm_CityEntity)) {
				io_AppendText(0x406d, *(unsigned short*) (o + 0x27), o, msg);
			} else {
				io_AppendText(0x406c, o, msg);
			}
			cnt++;
		}
		if (cnt != 0) {
			g_774a1c = 0;
			((struct deal*)d2_KanoneHitTable)[i].state = -1;
			d2_SetFormVisibility(*(int*) (w + 0x74), 1);
			return;
		}
		if (g_774a1c != 0) {
			g_774a1c = 0;
			((struct deal*)d2_KanoneHitTable)[i].state = -1;
			io_AppendText((int) "$C");
			io_AppendText(0x406e);
			d2_SetFormVisibility(*(int*) (w + 0x74), 1);
			return;
		}
	}
	d2_SetFormVisibility(*(int*) (w + 0x74), 0);
	g_774a1c = 0;
}
