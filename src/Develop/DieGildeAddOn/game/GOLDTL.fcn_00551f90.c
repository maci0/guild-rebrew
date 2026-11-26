#include "client_types.h"
#pragma pack(push, 1)
// SIZE 0xa9
typedef struct {
	unsigned char kind;
	int id;
	char pad5[0xa4];
} Player_551f90;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
// SIZE 0x24d
typedef struct {
	char type;
	char pad1[0x24c];
} Kind_551f90;
#pragma pack(pop)

#pragma pack(push, 2)
// SIZE 0xe






#pragma pack(pop)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0xd4
typedef struct {
	char pad0[0x52];
	pos14_7f4c00 stamp;
	char pad60[0x24];
	int event;
	char pad88[0x24];
	int who;
	int rnd;
	int value;
	char padb8[4];
	int ev[4];
	char padcc[4];
	int player;
} Order_551f90;


extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_data.h"


unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_004c5620(int, Order_551f90*);
void __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_SendAllocCharacter(int, int, int, int, int, int, const char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl he_BroadcastPlagueOutbreak(void);


/* ADDRESS: GOLDTL 0x00551f90 */
void __cdecl he_RunPlagueSpread(Order_551f90* o)
{
	char m[0xf8];
	char* fill;
	int n;
	Player_551f90* p;
	int i;

	o->stamp = (*(pos14_7f4c00*)&gm_GameTime);
	n = 0x100;
	i = gm_RandomMod(0x100);
	do {
		p = &((Player_551f90*)lpGebaeudeINST)[i];
		if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[p->kind].category) == 7) {
			o->rnd = gm_RandomMod(0x100);
			o->value = g_6643d8[gm_RandomMod(0x10)];
			n = sizeof(m);
			fill = m;
			/* align-up block fill: recorded C probes did not emit it
			 * (archived docs/codegen-walls.md 6b) */
			__asm {
				mov edi, fill
				mov ebx, n
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
			*(int*) (m + 0x58) = p->id;
			*(int*) (m + 0x5c) = p->id;
			*(int*) (m + 0x64) = o->rnd;
			*(int*) (m + 0x68) = o->value;
			*(int*) (m + 0x60) = -1;
			*(int*) (m + 0x6c) = o->who;
			*(int*) (m + 0xc) = -1;
			m[4] = 0x78;
			m[0x36] = 9;
			*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
			for (i = 0; i < 0x300; i++) {
				if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 6 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 7) {
					*(int*) (m + 8) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id;
					cm_SendCopyEntityData(m);
				}
			}
			o->ev[0] = cm_SendAllocCharacter(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[1] = cm_SendAllocCharacter(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[2] = cm_SendAllocCharacter(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[3] = cm_SendAllocCharacter(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->player = p->id;
			gm_AddTime(&o->stamp, 0, 1, 0);
			o->event = fcn_004c5620(0, o);
			he_BroadcastPlagueOutbreak();
			return;
		}
		n--;
		i = (i + 1) % 256;
	} while (n != 0);
	o->event = fcn_004c5620(-1, o);
}
