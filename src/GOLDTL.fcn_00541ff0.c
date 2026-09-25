// FUNCTION: GOLDTL 0x00541ff0
// SIZE: 499

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

extern Entity g_7f4ca0[];

void __cdecl fcn_004c4510(Entity*, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl fcn_005463a0(int, int, int, int, int);
float __cdecl fcn_00507540(int, int*);
void __cdecl fcn_004c5530(Msg*);
void __cdecl fcn_005100f0(int, int);

void __cdecl fcn_00541ff0(int index)
{
	float grade;
	int info[4];
	Msg msg;
	char text[0x100];
	Entity* e;
	int step;
	int busy;

	if (g_7f4ca0[index].type != 6 && g_7f4ca0[index].type != 7 && g_7f4ca0[index].type < 10) {
		int one;

		e = &g_7f4ca0[index];
		one = 1;
		if (g_7f4ca0[index].apprentice != 0 || g_7f4ca0[index].type == 5 || g_7f4ca0[index].type == 1
			|| g_7f4ca0[index].type == 2 || g_7f4ca0[index].type == 4) {
			fcn_004c4510(e, e->id);
			fcn_004c4670(4, 1, 0x174, &one);
			fcn_004c5360();
		}
		if (g_7f4ca0[index].trade != 0) {
			step = gm_GetOppositeStatIndex(g_7f4ca0[index].trade);
			busy = fcn_005463a0(2, 2, e->slot, 0, 0x24);
			e->busy++;
			grade = fcn_00507540(index, info);
			e->busy--;
			if (busy == 0 && step != 0 && step < 6 && grade >= 1.0 && g_7f4ca0[index].rank >= 0) {
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
	} else if (g_7f4ca0[index].type == 6 || g_7f4ca0[index].type == 7) {
		int flag;

		e = &g_7f4ca0[index];
		flag = 1;
		fcn_004c4510(e, e->id);
		fcn_004c4670(4, 1, 0x174, &flag);
		fcn_004c5360();
	}
}
