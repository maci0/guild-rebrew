#include <string.h>

char* __cdecl gm_SearchTable67(int);
int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl cm_SendRawEntityPacket(char*, int, char*);


/* ADDRESS: GOLD 0x004e48b0 */
/* ADDRESS: GOLDTL 0x004e6240 */
void __cdecl he_SendCmdMessage(int* a1, char* a2, char* text, char* extra)
{
	char message[0xf8];
	char buf[0x800];
	char* entity;
	char* query;
	int k;
	int n;

	memset(message, 0, sizeof(message));
	message[4] = 0x11;
	*(int*) (message + 0xc) = -1;
	message[0x36] = 9;
	*(int*) (message + 0x58) = 0x5ec;
	*(int*) (message + 8) = a1[1];
	k = *(int*) (a2 + 0x14);
	if (k != -1 && (a2[0x26] & 0x10) != 0)
		message[0x9c] = 0xe;
	else
		message[0x9c] = 0xc;
	*(int*) (message + 0x5c) = k;
	*(int*) (message + 0x64) = *(int*) a2;
	*(int*) (message + 0x60) = -1;
	if (k != -1) {
		entity = gm_SearchTable67(k);
		if (entity != 0) {
			if (gm_CheckEntityType(entity) == 0) {
				query = gm_SetupEntityQuery(entity);
				if (query != 0)
					*(int*) (message + 0x60) = *(int*) (query + 2);
			} else {
				query = fcn_00502cd0(*(int*) (entity + 0x5d), 1, 0, 0xfd);
				if (query != 0)
					*(int*) (message + 0x60) = *(int*) (query + 2);
			}
		}
	}
	strcpy(buf, text);
	n = strlen(buf) + 1;
	if (extra != 0 && *extra != 0) {
		memcpy(buf + n, extra, strlen(extra) + 1);
		message[0x9c] |= 0x10;
		cm_SendRawEntityPacket(message, strlen(extra) + n + 1, buf);
	} else {
		cm_SendRawEntityPacket(message, strlen(text) + 1, text);
	}
}
