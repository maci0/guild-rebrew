#ifndef AEMTER_H
#define AEMTER_H

extern char* g_14a5c6c[];

int __cdecl srv_GetEntityOfficeSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl srv_GetEntityCouncilSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);

/* Reconstructed byte-access contracts; original declarations are unproved. */
int __cdecl fcn_004e8240(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
int __cdecl fcn_004e81c0(unsigned char* a1, unsigned char* a2);

#endif
