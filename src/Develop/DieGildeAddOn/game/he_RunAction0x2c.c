#include <string.h>
#include "client_types.h"
#include "client_dialog_helpers.h"

extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca4[];

int __cdecl cm_GetCommandStatus(int id);
int __cdecl cm_SendSetHE(int a, char* unit);
void __cdecl fcn_004c5980(void* msg);
void __cdecl gm_AddTime(pos14_7f4c00* when, int h, int m, int s);
void __cdecl he_FreeAction(char* unit);
char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x0054ac70 */
void __cdecl he_RunAction0x2c(char* action)
{
	unsigned int pkt[0x45];
	char text[0x200];
	unsigned char* a;
	unsigned char* b;
	unsigned char* c;
	unsigned char* d;
	unsigned char* f;
	unsigned char* g;
	unsigned char kind;
	unsigned char* msg;
	int i;
	int waitId;

	if (*(int*) (action + 0x70) == -1 || *(int*) (action + 0x70) == -2) {
		he_FreeAction(action);
		return;
	}
	if (*(unsigned char*) (action + 0x78) & 4)
		return;
	waitId = *(int*) (action + 0x84);
	if (waitId != -1 && !cm_GetCommandStatus(waitId))
		return;
	*(int*) (action + 0x84) = -1;
	switch (*(int*) (action + 0x70)) {
	case 0:
		kind = (unsigned char) cm_GetCommandStatus(*(int*) (action + 0xd4));
		if (!kind)
			return;
		a = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xb0));
		b = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xac));
		c = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xb4));
		d = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xb8));
		f = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xbc));
		g = (unsigned char*) gm_LookupEntityRecordById(*(int*) (action + 0xc0));
		if (kind == 1) {
			*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) (action + 0xc5);
			if (a[2] == 6 || a[2] == 7) {
				io_FormatTextBuffer(text, 0x1bc0, *(unsigned short*) b, action + 0x52,
							 *(unsigned short*) (action + 0x56), *(unsigned short*) c,
							 *(unsigned short*) d, *(unsigned short*) f);
				he_PostEntityMessage(*(int*) (a + 4), *(int*) (a + 4), text, 0, 0x5f5,
							 (char*) 0x6a59e8);
			}
			if (b[2] == 6 || a[2] == 7) {
				io_FormatTextBuffer(text, 0x1bbf, *(unsigned short*) a, action + 0x52,
							 *(unsigned short*) (action + 0x56), *(unsigned short*) c,
							 *(unsigned short*) d, *(unsigned short*) f);
				he_PostEntityMessage(*(int*) (b + 4), *(int*) (b + 4), text, 1, 0x5f5,
							 (char*) 0x6a59d4);
			}
			io_FormatTextBuffer(text, 0x1bc1, *(unsigned short*) b, *(unsigned short*) a,
						 action + 0x52, *(unsigned short*) (action + 0x56));
			if (d[2] == 6 || d[2] == 7)
				he_PostEntityMessage(*(int*) (d + 4), *(int*) (d + 4), text, 0, 0x5f5,
							 (char*) 0x6a59c0);
			if (f[2] == 6 || f[2] == 7)
				he_PostEntityMessage(*(int*) (f + 4), *(int*) (f + 4), text, 0, 0x5f5,
							 (char*) 0x6a59c0);
			io_FormatTextBuffer(text, 0x1bc2, *(unsigned short*) b, *(unsigned short*) a,
						 action + 0x52, *(unsigned short*) (action + 0x56));
			if (c[2] == 6 || c[2] == 7)
				he_PostEntityMessage(*(int*) (c + 4), *(int*) (c + 4), text, 0, 0x5f5,
							 (char*) 0x6a59ac);
			if (g != 0 && (g[2] == 6 || g[2] == 7))
				he_PostEntityMessage(*(int*) (g + 4), *(int*) (g + 4), text, 0, 0x5f5,
							 (char*) 0x6a59ac);
			cm_SendSetHE(1, action);
			return;
		}
		if (kind != 2)
			return;
		if (b[2] == 6 || a[2] == 7) {
			io_FormatTextBuffer(text, 0x1bbe, *(unsigned short*) a);
			he_PostEntityMessage(*(int*) (b + 4), *(int*) (b + 4), text, 0, 0x5f5, 0);
		}
		*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		*(int*) (action + 0x58) = *(int*) (action + 0x58) + 2;
		cm_SendSetHE(-1, action);
		return;
	case 1:
		waitId = *(int*) (action + 0xac);
		msg = (unsigned char*) pkt;
		memset(pkt, 0, sizeof pkt);
		*(unsigned char*) (msg + 0x74) = *(unsigned char*) (action + 0xc4);
		*(int*) (msg + 0x7c) = *(int*) (action + 4);
		*(int*) (msg + 0x38) = *(int*) (action + 0xb0);
		*(int*) (msg + 0x44) = *(int*) (action + 0xbc);
		*(int*) (msg + 0x48) = *(int*) (action + 0xc0);
		*(int*) (msg + 0x3c) = *(int*) (action + 0xb4);
		*(unsigned char*) (msg + 0x30) =
			(unsigned char) ((*(int*) (action + 0xc0) != -1) + 5);
		*(int*) (msg + 0x40) = *(int*) (action + 0xb8);
		*(int*) (msg + 0x18) = gm_GameTime;
		*(unsigned char*) (msg + 8) = 2;
		*(unsigned char*) (msg + 0x26) = 0xa2;
		*(int*) (msg + 0x14) = -1;
		*(int*) (msg + 0x0c) =
		    *(int*) (g_7f4ca4 + (unsigned short) g_774970 * 0x21c);
		*(int*) (msg + 0x1c) = g_7f4c04;
		*(int*) (msg + 0x20) = g_7f4c08;
		*(unsigned short*) (msg + 0x24) = g_7f4c0c;
		*(int*) (msg + 0x34) = waitId;
		gm_AddTime((pos14_7f4c00*) (msg + 0x18), 0, 0x2d, 0);
		fcn_004c5980(pkt);
		gm_AddTime((pos14_7f4c00*) (action + 0x52), 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
		return;
	}
}
