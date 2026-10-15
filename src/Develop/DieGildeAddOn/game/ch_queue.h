#ifndef CH_QUEUE_H
#define CH_QUEUE_H

#include "client_types.h"

/* Inferred occupancy view of a 0x194-byte action slot; payload remains opaque. */
typedef struct CH_QUEUE_SLOT {
    int belegt;
    unsigned char unbekannt_004[0x190];
} CH_QUEUE_SLOT;

CH_QUEUE_SLOT* __cdecl ch_GetFreeQueueEntry(void);
int __cdecl fcn_004050c0(char* task);
void __cdecl fcn_00405180(void* object, void* task);
char* __cdecl ch_InsertAction(char* object, char* position, int kind, ...);

/* Native startup clears exactly 64 entries; declaration only, owner unresolved. */
/* ADDRESS: GOLDTL 0x014d0c40 */
/* ADDRESS: GOLD 0x01469700 */
extern Entry_14d0c40 g_14d0c40[64];

#endif
