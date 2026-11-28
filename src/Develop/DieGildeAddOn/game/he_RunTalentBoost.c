#include <float.h>
#include <string.h>



extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char s_6a5b74[];
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl gm_RandomMod(unsigned short n);
void __cdecl he_FreeAction(void* u);
void __cdecl cm_RequestModifyEntityLevel(int a1, int a2, int a3);
void __cdecl io_FormatTextBuffer(char* out, int a2, int a3, int a4);
void __cdecl he_PostEntityMessage(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl cm_SendCopyEntityData(void* packet);
void __cdecl cm_RequestUpdateResidenceDecor(int id);
int __cdecl sprintf(char*, const char*, ...);

#pragma optimize("y", off)

/* Sends one behaviour event to the server when its delay has elapsed. */
/* ADDRESS: GOLDTL 0x00551d50 */
void __cdecl he_RunTalentBoost(char* actionRecord)
{
	char buf[0x800];
	char packet[0xf8];
	char msg[0x20];
	char* row;
	int index;
	int delay;
	int byte;
	int id;
	int value;
	int fn;
	char* fp;

	if (*(int*) (actionRecord + 0x70) != -2) {
		if (*(int*) (actionRecord + 0x70) != 0) {
			return;
		}
		delay = *(unsigned char*) (actionRecord + 0xac) - (gm_RandomMod(*(unsigned char*) (actionRecord + 0xad)) & 0xffff);
		index = *(unsigned short*) (actionRecord + 8);
		byte = *(unsigned char*) (actionRecord + 0xae);
		row = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[index];
		id = *(unsigned char*) (row + 0x80 + byte);
		if ((float) (id + delay) > 252.0f) {
			delay = (int) (252.0f - (float) id);
		}
		cm_RequestModifyEntityLevel(*(int*) (row + 4), byte, delay);
		if (*(unsigned char*) (row + 2) == 6) {
			byte = *(unsigned char*) (actionRecord + 0xae);
			id = *(unsigned char*) (row + 0x80 + byte);
			value = (int) ((float) (id + delay) * 0.023809524f);
			if (value > (int) ((float) id * 0.023809524f)) {
				fn = 0xf8;
				fp = packet;
				__asm {
					mov edi, fp
					mov ebx, fn
					xor eax, eax
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L1
					rep stosb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep stosd
				L1:
					add ecx, ebx
					rep stosb
				}
				*(int*) (packet + 8) = *(int*) (row + 4);
				*(int*) (packet + 0x28) = gm_GameTime;
				*(int*) (packet + 0x2c) = gm_GameTimeHour;
				*(int*) (packet + 0x30) = gm_GameTimeSliceDword;
				*(short*) (packet + 0x34) = gm_GameTimeTailWord;
				*(char*) (packet + 4) = 0x6a;
				*(int*) (packet + 0xc) = -1;
				*(char*) (packet + 0x36) = 9;
				*(char*) (packet + 0x58) = *(unsigned char*) (actionRecord + 0xae);
				*(int*) (packet + 0x5c) = value;
				cm_SendCopyEntityData(packet);
			} else {
				sprintf(msg, s_6a5b74, byte);
				io_FormatTextBuffer(buf, 0x67728c, 0x16f2, *(unsigned char*) (actionRecord + 0xae) + 0x16f3);
				id = ((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(actionRecord + 8)].entity_id;
				he_PostEntityMessage(id, id, buf, 0, 0x5fd, msg);
			}
		}
		cm_RequestUpdateResidenceDecor(*(int*) (row + 4));
		he_FreeAction(actionRecord);
		return;
	}
	he_FreeAction(actionRecord);
}
