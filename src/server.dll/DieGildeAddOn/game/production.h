#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "../../game_common.h"
#include "../../game_structs.h"
#include "game.h"

/* Production and Crafting */
extern int __cdecl gm_CalculateProductionValue(int object_id);
extern int __cdecl gv_UpdateProductionProgress(void* building);
extern void __cdecl gv_ExtendProductionTime(void* building, int added_time);

/* Alchemistry Specific */
extern int __cdecl ahm_AllocAhmInfo(void);
extern int __cdecl ahm_ExAllocAlchemist(unsigned int* param_1, unsigned char* param_2);

/* Building Production */
extern int __cdecl gm_SumBuildingProductionValues(void* building);
extern int __cdecl cm_GetBuildingStatCount(void* building, int type);

/* Worker Management */
extern int __cdecl cm_ExEmployWorker(void* building, void* worker);
extern int __cdecl gv_HireProductionWorker(void* building);
extern int __cdecl gv_ReplaceProductionWorker(void* building, void* old_worker, void* new_worker);

#endif /* PRODUCTION_H */
