#include "Develop/DieGildeAddOn/game/game_player.h"
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
int __cdecl srv_GetEntityOfficeSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl amt_SendOfficeCommand(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
void __cdecl io_FormatTextBuffer(void* out, int id, ...);
int __cdecl he_PostEntityMessage(int id, int arg, char* text1, unsigned char flags, int value, char* text2);

void __cdecl fcn_004e04f0(char* a0)
{
	char* first;
	char* second;
	char* w;
	char* p;
	int slot[6];
	int role[6];
	char buf[0x400];

	first = gm_LookupEntityRecordById(*(int*) (a0 + 0x34));
	second = gm_LookupEntityRecordById(*(int*) (a0 + 0x38));
	if (first != 0 && second != 0) {
		w = gm_GetEntitySkill(first, 3) > gm_GetEntitySkill(second, 3) ? second : first;
		if (*(unsigned char*) (w + 0x166) != 0) {
			if (srv_GetEntityOfficeSlot((unsigned char*) w, role, slot) != 0) {
				if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + g_774970 * 0x21c)) {
					amt_SendOfficeCommand(*(unsigned char*) slot, 0, 0, 4, 0xff);
					p = (char*) 0x7f4ca2;
					do {
						if (*p == 6 || *p == 7) {
							io_FormatTextBuffer(buf, 0x10c7, *(unsigned short*) w, (*(unsigned char*) (w + 9) != 0) + 0x10c8);
							he_PostEntityMessage(*(int*) (p + 2), -1, buf, 0, 0x5fe, (char*) 0x6b5c60);
						}
						p += 0x21c;
					} while ((int) p < 0x85a0a2);
				}
			}
		}
	}
}
