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

#endif
