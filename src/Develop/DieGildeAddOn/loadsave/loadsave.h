#ifndef LOADSAVE_H
#define LOADSAVE_H

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
int __cdecl ls_LoadSavegameHeader(void* stream, char* dest);
int __cdecl ls_LoadExistingEntities(void* stream);
unsigned int __cdecl ls_LoadBuildingEntityState(void* stream);
int __cdecl ls_LoadDynamicEntities(void* stream);
int __cdecl ls_LoadEntities(void* stream);
int __cdecl ls_LoadTownData(void* stream);
int __cdecl ls_LoadRelationships(void* stream);
int __cdecl ls_LoadGraveyardData(void* stream, unsigned char* field);

#endif /* LOADSAVE_H */
