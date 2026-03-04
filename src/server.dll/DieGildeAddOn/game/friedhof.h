#ifndef FRIEDHOF_H
#define FRIEDHOF_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Graveyard Management (Friedhof) */
extern int __cdecl SpawnGraveyardEntities(void);
extern int __cdecl AllocGraveyardField(int field_id);
extern int __cdecl UpgradeGraveyardField(int field_id);
extern void __cdecl ActivateGraveyardSection(int section_id);

/* Allocation wrappers */
extern int __cdecl gv_ExAllocGraveyardWorker(unsigned int* param_1, unsigned char* param_2);

#endif /* FRIEDHOF_H */
