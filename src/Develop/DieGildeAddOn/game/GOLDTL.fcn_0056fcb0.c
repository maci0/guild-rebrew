#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_slot_table[2];

void __cdecl he_FreeAction(char* e);
float __cdecl gm_CalcActionCompletionTime(int idx, int* info);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl gm_AddTime(void*, int, int, int);

/* Drives the dozing state of one entity: a negative record flag resets the
 * timer, a sub-1.0 rest value keeps it idle for 0x14, otherwise a 0x25 packet
 * is queued and the record is marked busy. */
/* ADDRESS: GOLDTL 0x0056fcb0 */
void __cdecl fcn_0056fcb0(char* e)
{
	int info[4];
	char msg[0xf8];
	int state;

	state = *(int*) (e + 0x70);
	if (state < -2) {
		return;
	}
	if (state >= 0) {
		if (state != 0) {
			return;
		}
		if ((*(int*) (g_slot_table + (*(unsigned short*) (e + 8)) * 0x21c + 0x1c8) & 0x80000000) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime(e + 0x52, 4, 0, 0);
			return;
		}
		if (gm_CalcActionCompletionTime(*(unsigned short*) (e + 8), info) >= 1.0) {
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x25;
			*(int*) (msg + 0xc) = -1;
			msg[0x36] = 9;
			*(int*) (msg + 0x60) = 2;
			*(int*) (msg + 8) = *(int*) (g_slot_table + (*(unsigned short*) (e + 8)) * 0x21c + 4);
			*(int*) (msg + 0x58) = *(int*) (g_slot_table + (*(unsigned short*) (e + 8)) * 0x21c + 4);
			cm_SendCopyEntityData(msg);
			*(int*) (g_slot_table + (*(unsigned short*) (e + 8)) * 0x21c + 0x1c8) |= 0x80000000;
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime(e + 0x52, 4, 0, 0);
			return;
		}
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime(e + 0x52, 0, 0x14, 0);
	} else {
		he_FreeAction(e);
	}
}
