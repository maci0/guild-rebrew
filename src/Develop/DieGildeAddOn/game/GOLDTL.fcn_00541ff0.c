


#include <stdio.h>
#include <string.h>

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x15c];
	unsigned char trade;
	char pad165[7];
	int apprentice;
	char pad170[4];
	int busy;
	char pad178[0x1c];
	int rank;
	char pad198[0x84];
} Entity;

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int id;
	int target;
	char pad10[0x26];
	char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	int x64;
	char pad68[0x90];
} Msg;

#include "Develop/DieGildeAddOn/game/entity_record.h"

#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
float __cdecl fcn_00507540(int, int*);
void __cdecl fcn_004c5530(Msg*);
void __cdecl fcn_005100f0(int, int);

void __cdecl gm_UpdateEntityAgingAndTraining(int index)
{
	float grade;
	int info[4];
	Msg msg;
	char text[0x100];
	Entity* e;
	int step;
	int busy;

	if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) != 6 && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) != 7 && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) < 10) {
		int one;

		e = ((Entity*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[index]);
		one = 1;
		if ((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].ptr_16c) != 0 || (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 5 || (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 1
			|| (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 2 || (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 4) {
			cm_BeginPacketFieldDelta((char*) e, e->id);
			fcn_004c4670(4, 1, 0x174, &one);
			fcn_004c5360();
		}
		if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].stat_category) != 0) {
			step = gm_GetOppositeStatIndex((((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].stat_category));
			busy = he_StartHandlungSearch(2, 2, e->slot, 0, 0x24);
			e->busy++;
			grade = fcn_00507540(index, info);
			e->busy--;
			if (busy == 0 && step != 0 && step < 6 && grade >= 1.0 && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].value_194) >= 0) {
				memset(&msg, 0, sizeof(msg));
				msg.x64 = 0;
				msg.x5c = 0;
				msg.type = 0x24;
				msg.id = e->id;
				msg.target = -1;
				msg.x36 = 0x11;
				msg.x60 = 1;
				msg.x58 = e->id;
				fcn_004c5530(&msg);
				sprintf(text, "MeisterPr\xfc" "fung started: player_id:%i beruf:%i grad:%i", e->id, e->trade, step + 1);
				fcn_005100f0(e->id, -4);
			}
		}
	} else if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 6 || (((ENTITY_RECORD_VIEW*)g_7f4ca0)[index].entity_type) == 7) {
		int flag;

		e = ((Entity*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[index]);
		flag = 1;
		cm_BeginPacketFieldDelta((char*) e, e->id);
		fcn_004c4670(4, 1, 0x174, &flag);
		fcn_004c5360();
	}
}
