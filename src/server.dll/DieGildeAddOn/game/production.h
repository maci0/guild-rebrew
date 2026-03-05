#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "../../game_common.h"
#include "../../game_structs.h"
#include "game.h"

/* Production and Crafting */
extern int __cdecl CalculateProductionValue(int object_id);
extern int __cdecl UpdateProductionProgress(void* building);
extern void __cdecl ExtendProductionTime(void* building, int added_time);

/* Alchemistry Specific */
extern int __cdecl ahm_AllocAhmInfo(void);
extern int __cdecl ahm_ExAllocAlchemist(unsigned int* param_1, unsigned char* param_2);

/* Building Production */
extern int __cdecl SumBuildingProductionValues(void* building);
extern int __cdecl GetBuildingStatCount(void* building, int type);

/* Worker Management */
extern int __cdecl EmployWorkerAtBuilding(void* building, void* worker);
extern int __cdecl HireProductionWorker(void* building);
extern int __cdecl ReplaceProductionWorker(void* building, void* old_worker, void* new_worker);

#endif /* PRODUCTION_H */
