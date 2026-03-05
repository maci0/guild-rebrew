#ifndef AUXILLARY_H
#define AUXILLARY_H

#include "../../game_common.h"

/* Record and Zone Lookup */
extern void* __cdecl plt_FindRecord(int id);
extern void* __cdecl plt_FindZoneRecord(int zone_id);
extern int __cdecl plt_CheckZoneAvailability(int zone_id, int type);

/* Plant and Environment */
extern void __cdecl plt_SetPlantMap(void* map_data);

/* Low-level table utilities */
extern void* __cdecl plt_TableLookup(int index);

#endif /* AUXILLARY_H */
