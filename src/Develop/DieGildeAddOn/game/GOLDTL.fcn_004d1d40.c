

extern char* g_773db4[];
extern unsigned char g_773d75;
#include "client_packet_builder.h"

int __cdecl fcn_004d0cd0(int* a);
void __cdecl gm_RemoveSpecialTableItems(char* u);
int __cdecl cm_SendSellObjekt(int a, int b, int c, int d, char e, int f);
float __cdecl fcn_004ff210(unsigned short id, int delta);

int __cdecl cm_AppendPacketFieldDelta(unsigned char size, unsigned char count, unsigned short off, unsigned char* src);
void __cdecl cm_RequestChangeAttribute(void);

/* v is a separate local: c2 homes it in the dead slot of mode, and mode
 * stays a register load (an &mode argument would force byte reloads). */
void __cdecl gm_EquipDuelist(char* obj, unsigned char mode)
{
	int i;
	unsigned char v;

	if (mode != 0) {
		*(int*) (obj + 0x110) = mode;
	}
	if (mode == 1) {
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		gm_RemoveSpecialTableItems(g_773db4[i]);
		cm_SendSellObjekt(*(int*) (g_773db4[i] + 4), -1, 0x156, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xa8;
		cm_BeginPacketFieldDelta(g_773db4[i], *(int*) (g_773db4[i] + 4));
		cm_AppendPacketFieldDelta(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		cm_RequestChangeAttribute();
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		gm_RemoveSpecialTableItems(g_773db4[i]);
		cm_SendSellObjekt(*(int*) (g_773db4[i] + 4), -1, 0x156, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xa8;
		cm_BeginPacketFieldDelta(g_773db4[i], *(int*) (g_773db4[i] + 4));
		cm_AppendPacketFieldDelta(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		cm_RequestChangeAttribute();
	}
	else if (mode == 2 || mode == 3) {
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		gm_RemoveSpecialTableItems(g_773db4[i]);
		cm_SendSellObjekt(*(int*) (g_773db4[i] + 4), -1, 0x158, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xd2;
		cm_BeginPacketFieldDelta(g_773db4[i], *(int*) (g_773db4[i] + 4));
		cm_AppendPacketFieldDelta(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		cm_RequestChangeAttribute();
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		gm_RemoveSpecialTableItems(g_773db4[i]);
		cm_SendSellObjekt(*(int*) (g_773db4[i] + 4), -1, 0x160, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xd2;
		cm_BeginPacketFieldDelta(g_773db4[i], *(int*) (g_773db4[i] + 4));
		cm_AppendPacketFieldDelta(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		cm_RequestChangeAttribute();
	}
}
