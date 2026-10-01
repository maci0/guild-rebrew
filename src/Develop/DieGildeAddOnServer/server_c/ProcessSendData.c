extern unsigned char g_connections[9 * 0x264264];
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
int __cdecl ProcessSendData(void);

#include "../server_internal.h"

int __cdecl srv_SendPlayerData(unsigned int*);

// FUNCTION: SERVER 0x1000a860
// ProcessSendData
void __cdecl list_unlink_relink(char* ctx, char* node);

int __cdecl ProcessSendData(void)
{
	unsigned char* slot_cursor;
	int result;
	unsigned int* pkt;

	slot_cursor = g_connections;
	do {
		if ((slot_cursor[0] & 1) != 0) {
			result = srv_SendPlayerData((unsigned int*) slot_cursor);
			if (result == -1) {
				return -1;
			}
			while (1) {
				pkt = *(unsigned int**) (slot_cursor + 0x2641f4);
				if (pkt == 0 || (*(unsigned int*) slot_cursor & 0x100) == 0) {
					break;
				}
				memcpy(slot_cursor + 0xb1, pkt, 0x99);
				list_unlink_relink((char*) slot_cursor, *(char**) (slot_cursor + 0x2641f4));
				*(unsigned int*) slot_cursor &= ~0x100;
				result = srv_SendPlayerData((unsigned int*) slot_cursor);
				if (result == -1) {
					return -1;
				}
			}
			if (result == -1) {
				return -1;
			}
		}
		slot_cursor += 0x264264;
	} while ((int) slot_cursor < (int) (g_connections + 0x1321320));
	return 0;
}
