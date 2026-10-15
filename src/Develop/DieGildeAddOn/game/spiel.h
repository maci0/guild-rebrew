#ifndef SPIEL_H
#define SPIEL_H

struct LinkedNode;
int __cdecl gm_FreeObjectListRecursive(struct LinkedNode** head);
void __cdecl gm_ClearObjektResources(struct LinkedNode* node);
#ifndef REBREW_SERVER
extern char* g_99ec10;
void __cdecl fcn_004be280(char* list);
#endif

int __cdecl gm_WalkEntityChain(unsigned short raw_idx);

#ifndef SPIEL_EARLY_STAT_DECLARATIONS
int __cdecl gm_MapEntityStatRange(int stat_id);
short* __cdecl gm_GetEntityTableEntry(char* entity);
#endif

/* Shared entity lookup and type classification. */
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gm_GetBuildingTypeCategory(int type);

/* Reconstructed entity byte-access contracts; original spellings are unproved. */
#ifndef REBREW_SERVER
float __cdecl fcn_00507f10(char* entity, int index);
int __cdecl fcn_00507e30(char* entity, int index);
float __cdecl fcn_00507e70(char* first, char* second, int index);
#endif

#endif
