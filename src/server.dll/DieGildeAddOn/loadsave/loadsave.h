#ifndef LOADSAVE_H
#define LOADASVE_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Savegame Header */
extern int __cdecl ls_LoadSavegameHeader(char* filename, void* header);

/* Persistence for Game Modules */
extern int __cdecl ls_LoadTownData(int handle);
extern int __cdecl ls_LoadGraveyardData(int handle);
extern int __cdecl ls_LoadBuildingEntityState(int handle);

/* Entity state restoration */
extern int __cdecl ls_LoadExistingEntities(int handle);
extern int __cdecl ls_LoadDynamicEntities(int handle);

/* ID mapping */
extern void* __cdecl ls_ID2Ptr(int id);
extern int __cdecl ls_LoadEntities(int handle);

#endif /* LOADSAVE_H */
