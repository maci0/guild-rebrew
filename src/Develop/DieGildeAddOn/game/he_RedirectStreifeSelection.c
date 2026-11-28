extern int g_7e4318;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];

/* SIZE 0xf8: stack message sent through fcn_004c5530 */
typedef struct {
	int h0;
	unsigned char kind;
	char p5[3];
	int owner;
	char pc[0x2a];
	unsigned char flag36;
	char p37[0x21];
	int v58;
	int v5c;
	char p60[0x10];
	int ids[4];
	char p80[0x78];
} STREIFE_REDIRECT_MSG;

char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl cm_SendCopyEntityData(STREIFE_REDIRECT_MSG*);

/* ADDRESS: GOLDTL 0x00531320 */
void __cdecl he_RedirectStreifeSelection(void)
{
	STREIFE_REDIRECT_MSG msg;
	int* cursor;
	char* row;
	char* hit;
	char* p;
	char* r;
	int count;
	int first;
	int state;
	int done;
	int g;
	int i;

	g = g_7e4318;
	cursor = msg.ids;
	count = 0;
	done = 0;
	state = 0;
	hit = 0;
	first = 0;
	msg.kind = 0;
	for (row = (char*) 0x7f4e0c; (int) row < 0x85a20c; row += 0x21c) {
		if (done != 0) {
			break;
		}
		if (*(char*) (row + 0x1c) == 0) {
			continue;
		}
		if (state == 0) {
			p = *(char**) (row + 0x10);
			if (p == 0 || *(int*) row == 0) {
				goto next;
			}
			state = 0x43;
			hit = p;
			if (*p != 'C') {
				goto next;
			}
			if (*(int*) row != g) {
				msg.kind = 'C';
				msg.flag36 = 2;
				first = *(int*) row;
				cursor++;
				msg.owner = *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c);
				msg.v58 = *(int*) (g + 1);
				msg.v5c = *(int*) (*(int*) row + 1);
				cursor[-1] = *(int*) (row - 0x168);
				count++;
				if (count < 4) {
					for (i = 0; i < 4 - count; i++) {
						cursor[i] = -1;
					}
				}
				for (i = 0; i < 4; i++) {
					if (*(int*) (hit + 0xc4 + i * 4) == *(int*) (row - 0x168)) {
						*(int*) (hit + 0xc4 + i * 4) = -1;
						g = g_7e4318;
						break;
					}
				}
				goto next;
			}
			r = fcn_00502cd0(*(int*) (g + 0x5d), 1, 0, 0x146);
			for (i = 0; i < 4; i++) {
				if (*(int*) (hit + 0xc4 + i * 4) == *(int*) (row - 0x168)) {
					*(int*) (hit + 0xc4 + i * 4) = -1;
					break;
				}
			}
			he_AssignActionSlot((char*) g_7e4318, 0, *(unsigned short*) (row - 0x16c), 0);
			cm_SendCancelCharacterActions(*(int*) (row - 0x168));
			ch_StartMovement(*(int*) (row - 0x168), *(int*) (g_7e4318 + 1), *(int*) (r + 2), 0, 0, 0);
			g = g_7e4318;
		} else {
			if (state != 0x43 || *(int*) row != first || *(char**) (row + 0x10) != hit) {
				goto next;
			}
			if (*(int*) row != g) {
				*cursor = *(int*) (row - 0x168);
				count++;
				cursor++;
				for (i = 0; i < 4; i++) {
					if (*(int*) (hit + 0xc4 + i * 4) == *(int*) (row - 0x168)) {
						*(int*) (hit + 0xc4 + i * 4) = -1;
						g = g_7e4318;
						break;
					}
				}
				if (count > 3) {
					done = 1;
				}
				goto next;
			}
			r = fcn_00502cd0(*(int*) (g + 0x5d), 1, 0, 0x146);
			for (i = 0; i < 4; i++) {
				if (*(int*) (hit + 0xc4 + i * 4) == *(int*) (row - 0x168)) {
					*(int*) (hit + 0xc4 + i * 4) = -1;
					break;
				}
			}
			he_AssignActionSlot((char*) g_7e4318, 0, *(unsigned short*) (row - 0x16c), 0);
			cm_SendCancelCharacterActions(*(int*) (row - 0x168));
			ch_StartMovement(*(int*) (row - 0x168), *(int*) (g_7e4318 + 1), *(int*) (r + 2), 0, 0, 0);
			g = g_7e4318;
		}
	next:
		*(char*) (row + 0x1c) = 0;
	}
	if (hit != 0) {
		cm_SendSetHE(*(int*) (hit + 0x70), hit);
	}
	if (msg.kind != 0) {
		cm_SendCopyEntityData(&msg);
	}
}
