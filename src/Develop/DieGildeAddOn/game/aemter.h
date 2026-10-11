#ifndef AEMTER_H
#define AEMTER_H

extern char* g_14a5c6c[];

int __cdecl srv_GetEntityOfficeSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl srv_GetEntityCouncilSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);

#endif
