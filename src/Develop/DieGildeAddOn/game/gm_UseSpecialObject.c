


typedef struct Ent {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x170 - 8];
	char* home;
	char pad174[0x1ec - 0x174];
	int flags;
} Ent;
// SIZE 0x1f0

typedef struct Cmd {
	unsigned short* rec;
	char pad4[8];
	int shown;
	int done;
} Cmd;
// SIZE 0x14

typedef struct Desc {
	char pad0[4];
	int value;
	int action;
	char padc[4];
	int flags;
	int (__cdecl* run)(Ent*, Cmd*);
} Desc;
// SIZE 0x18

#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int g_7f4c06;
extern int g_7f4c0a;
extern unsigned char gm_ActiveTownIndex;

Desc* __cdecl gm_LookupSpecialObject(int);
double __cdecl gm_RandomFloat01(void);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, void*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);
char* __cdecl gm_LookupSpecialObjectRecord(int, int*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowUseObjDialog(char*);

/* ADDRESS: GOLDDE 0x005bd4b0 */
int __cdecl gm_UseSpecialObject(Ent* ent, Cmd* cmd)
{
	char one;
	int result;
	int v8;
	int vc;
	char text[0x800];
	Desc* d;
	char* rec;

	if (ent == 0) {
		return -1;
	}
	if (cmd == 0) {
		return -2;
	}
	cmd->done = 0;
	if (cmd->rec == 0) {
		return -3;
	}
	d = gm_LookupSpecialObject(*cmd->rec);
	if (d == 0) {
		return -4;
	}
	if (ent->flags & d->flags) {
		return -5;
	}
	cmd->shown = *cmd->rec != 0x175 || gm_RandomFloat01() >= 0.66;
	if (d->run != 0) {
		result = d->run(ent, cmd);
	} else {
		result = 1;
	}
	if (result != 0) {
		d2_DispatchTutorialInput(0x2d, 0, 0, *cmd->rec);
		if (d->flags != 0) {
			cm_RequestChangeBits(ent->handle, 0x1ec, 4, d->flags, 0);
		}
		if (d->value != 0) {
			vc = d->value;
			v8 = 1;
			one = 1;
			cm_BeginPacketFieldDelta((char*) cmd->rec, *(int*) (cmd->rec + 1));
			cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x1c), &vc);
			cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x21), &v8);
			cm_AppendPacketFieldDelta(1, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x20), &one);
			cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x2d), &(*(int*)&gm_GameTime));
			cm_AppendPacketFieldDelta(2, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x31), &(*(short*)&gm_GameTimeHour));
			cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x33), &g_7f4c06);
			cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((char*) cmd->rec - cm_PacketDeltaBase + 0x37), &g_7f4c0a);
			cm_RequestChangeAttribute();
		}
		if (d->value == 0) {
			cm_SendSellObjekt(-1, ent->handle, *cmd->rec, 1, gm_ActiveTownIndex, 0);
		}
		if (d->action != -1) {
			if (ent->home) {
				gm_TryRecordCrime(d->action, 1, ent->handle, -1, *(int*) (ent->home + 1));
			} else {
				gm_TryRecordCrime(d->action, 1, ent->handle, -1, -1);
			}
		}
		if (ent->kind == 6 && cmd->done == 0) {
			rec = gm_LookupSpecialObjectRecord(*cmd->rec, &v8);
			if (cmd->shown == 1) {
				io_FormatTextBuffer(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1);
			}
			d2_ShowUseObjDialog(text);
		}
	}
	return result;
}
