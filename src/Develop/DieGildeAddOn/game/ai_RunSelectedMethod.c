#include "Develop/DieGildeAddOn/game/client_method_registry.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern AM_METHOD am_Methods[];
extern char* ai_FeudTargetEntity;

void __cdecl cm_BeginSecondaryPacketDelta(void*);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_SendChangeDesire(void);
void __cdecl cm_AppendDesireDelta(int, float);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00495690 */
int __cdecl ai_RunSelectedMethod(int entity_idx)
{
	ENTITY_RECORD* entity;
	void* fn;
	int i;

	entity = &((ENTITY_RECORD*) gm_EntitySlotTable)[entity_idx];
	if (((ENTITY_RECORD*) gm_EntitySlotTable)[entity_idx].unk_132) {
		fn = am_Methods[((ENTITY_RECORD*) gm_EntitySlotTable)[entity_idx].unk_132].run;
		if (fn && ((int (__cdecl*) (void*, void*, void*)) fn) (entity, (char*) entity + 0x134, (char*) entity + 0x14c)) {
			cm_BeginSecondaryPacketDelta(entity);
			for (i = 0; i < 4; i++) {
				if (am_Methods[entity->unk_131].effects[i].type < 0xe)
					cm_AppendDesireDelta(am_Methods[entity->unk_131].effects[i].type,
						am_Methods[entity->unk_131].effects[i].value * -0.5f);
			}
			for (i = 0; i < 4; i++) {
				if (am_Methods[entity->unk_132].effects[i].type < 0xe)
					cm_AppendDesireDelta(am_Methods[entity->unk_132].saved_effects[i].type,
						am_Methods[entity->unk_132].saved_effects[i].value * -0.5f);
			}
			if (entity->unk_131 == entity->unk_132) {
				cm_AppendDesireDelta(0xd, 500.0f);
				if (ai_FeudTargetEntity && *(int*) (ai_FeudTargetEntity + 4) == entity->unk_210) {
					*(unsigned char*) &entity_idx = 2;
					cm_BeginPacketFieldDelta(entity, entity->entity_id);
					cm_AppendPacketFieldValue(1, 1, 0x215, &entity_idx);
					cm_RequestChangeAttribute();
				}
			} else {
				cm_AppendDesireDelta(0xd, 250.0f);
				if (ai_FeudTargetEntity && *(int*) (ai_FeudTargetEntity + 4) == entity->unk_210) {
					*(unsigned char*) &entity_idx = 1;
					cm_BeginPacketFieldDelta(entity, entity->entity_id);
					cm_AppendPacketFieldValue(1, 1, 0x215, &entity_idx);
					cm_RequestChangeAttribute();
				}
			}
			cm_SendChangeDesire();
			fcn_0064d740(am_Methods[entity->unk_132].saved_effects, am_Methods[entity->unk_132].effects, 0x20);
			return 1;
		}
	}
	if (ai_FeudTargetEntity && *(int*) (ai_FeudTargetEntity + 4) == entity->unk_210) {
		*(unsigned char*) &entity_idx = 3;
		cm_BeginPacketFieldDelta(entity, entity->entity_id);
		cm_AppendPacketFieldValue(1, 1, 0x215, &entity_idx);
		cm_RequestChangeAttribute();
	}
	return 0;
}
unsigned char _dpad_77261c[672];
