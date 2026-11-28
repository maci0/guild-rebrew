#include "Develop/DieGildeAddOn/game/client_data.h"
extern int g_773d48;
#pragma pack(2)
typedef struct {
	unsigned char kind;
	char pad1[1];
	int id;
	unsigned char active;
	unsigned char b7;
	unsigned short value;
	char pad10[0x1e - 0xa];
	float pos;
	char pad22[0x182 - 0x22];
	int flag;
	char pad186[0x21c - 0x186];
} ENTITY_UPDATE_SLOT;
#pragma pack()

void __cdecl cm_StepCommandQueue(void);
void __cdecl cm_BeginPacketFieldDelta(char* base, int entity_id);
int __cdecl cm_AppendPacketFieldDelta(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl cm_RequestChangeAttribute(void);
float __cdecl gm_AgeAndUpdateEntity(void*);
void __cdecl cm_SendSwapEntityModel(int entity_id, char* model_name);
void __cdecl gm_MaintainNpcPopulation(void);

/* ADDRESS: GOLDTL 0x004ff0f0 */
void __cdecl gm_UpdateActiveEntities(void)
{
	ENTITY_UPDATE_SLOT* p;

	int v;
	int id;


	g_773d48 = 0;
	p = (ENTITY_UPDATE_SLOT*) g_7f4ca2;
	do {
		if (g_773d48 > 0x40) {
			cm_StepCommandQueue();
			g_773d48 = 0;
		}
		if (p->kind == 0x12) {
			id = p->id;
			v = 8;
			cm_BeginPacketFieldDelta((char*) p - 2, id);
			cm_AppendPacketFieldDelta(1, 1, 2, (char*) &v);
			cm_RequestChangeAttribute();
			++g_773d48;
		}
		p++;
	} while ((int) p < (int) &g_7f4ca2[768]);
	p = (ENTITY_UPDATE_SLOT*) g_7f4ca2;
	do {
		if (g_773d48 > 0x40) {
			cm_StepCommandQueue();
			g_773d48 = 0;
		}
		if ((p->kind < 10 || p->kind == 0x14)
		    && p->active != 0) {
			gm_AgeAndUpdateEntity((char*) p - 2);
			v = p->value;
			if ((float) v == p->pos - 1.0f
			    && p->flag != 0) {
				if (p->b7 == 0) {
					cm_SendSwapEntityModel(p->id, (char*) 0x696514);
				}
				else {
					cm_SendSwapEntityModel(p->id, (char*) 0x696508);
				}
				++g_773d48;
			}
		}
		p++;
	} while ((int) p < (int) &g_7f4ca2[768]);
	gm_MaintainNpcPopulation();
	g_773d48 = 0;
}
