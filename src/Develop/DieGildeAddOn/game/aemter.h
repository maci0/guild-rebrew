#ifndef AEMTER_H
#define AEMTER_H

#include "../../game_structs.h"

extern char* amt_OfficeNames[];

int __cdecl srv_GetEntityOfficeSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl srv_GetEntityCouncilSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);

/* Reconstructed byte-access contracts; original declarations are unproved. */
int __cdecl amt_SendOfficeCommand(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
int __cdecl amt_AssignEntityOfficeDefault(unsigned char* a1, unsigned char* a2);
int __cdecl amt_FindOfficeSlotsByKind(int kind, int max, OFFICE_SLOT* out);

#endif
