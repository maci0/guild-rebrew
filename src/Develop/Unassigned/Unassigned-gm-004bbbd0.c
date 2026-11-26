typedef struct {
	int who;
	unsigned short op;
} fcn_004bbbd0_msg;

typedef int(__cdecl* fcn_004bbbd0_handler)(fcn_004bbbd0_msg*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern fcn_004bbbd0_handler g_6811b8[];

char* __cdecl gm_LookupEntityRecordById(int);
#include <string.h>





extern int g_7728e0;

__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
int __cdecl fcn_004bbce0(int);
void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDTL 0x004bbbd0 */
int __cdecl gm_DispatchEntityMessage(fcn_004bbbd0_msg* msg)
{
	char* entity;

	if ((*(int*)&gm_GameTime) < 8)
		return 0;
	if (msg == 0)
		return -1;
	entity = gm_LookupEntityRecordById(msg->who);
	if (entity == 0 || *(unsigned char*) (entity + 0x1b1) > 0)
		return 0x400;
	if (msg->op < 0x45)
		return g_6811b8[msg->op](msg);
	return -2;
}

/* ADDRESS: GOLD 0x004bb720 */
/* ADDRESS: GOLDTL 0x004bbc30 */
int __cdecl fcn_004bbc30(int a1, int a2)
{
	char packet[0xf8];
	int count;
	int i;

	count = fcn_004bbce0(a1 + 1);
	g_7728e0 = GetTickCount();
	memset(packet, 0, sizeof(packet));
	packet[4] = 0x42;
	*(int*) (packet + 8) = a2;
	*(int*) (packet + 0xc) = -1;
	*(pos14_7f4c00*) (packet + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	packet[0x36] = 1;
	for (i = 0; i < count; i++) {
		*(short*) (packet + 0x5c) = fcn_004bbce0(0x45);
		*(int*) (packet + 0x58) = a2;
		cm_SendCopyEntityData(packet);
	}
	return count;
}

/* ADDRESS: GOLDTL 0x004bbce0 */
unsigned int __cdecl fcn_004bbce0(unsigned int n)
{
	if (n == 0)
		return 0;
	(*(unsigned int*)&g_7728e0) = (*(unsigned int*)&g_7728e0) * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &(*(unsigned int*)&g_7728e0) + 1) % 0x7fffu % n;
}
