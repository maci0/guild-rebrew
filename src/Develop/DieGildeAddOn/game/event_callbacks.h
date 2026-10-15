#ifndef EVENT_CALLBACKS_H
#define EVENT_CALLBACKS_H

/* Inferred validator contract and declaration home; the event remains a byte view. */
typedef int (__cdecl* EVENT_CHECK)(char* event);

/* The first three slots store callback addresses; their call contracts remain open. */
void __cdecl fcn_004e7160(int kind, void* first, void* second, void* third,
    EVENT_CHECK check, unsigned char flag);

/* Reconstructed court decision callback; other phase-slot contracts remain open. */
void __cdecl fcn_004df1b0(char* participant, int* action);

/* Existing event helpers use word and unsigned-byte access views. */
void __cdecl fcn_004e5a00(int* event);
int __cdecl fcn_004e64e0(int* event);
int __cdecl fcn_004e6200(int participant, unsigned char* event);
int __cdecl cut_CheckMaster(int* event);

int __cdecl fcn_004dc7d0(char* event);
int __cdecl fcn_004d74b0(char* event);
int __cdecl fcn_004e1330(char* event);
int __cdecl fcn_004e1960(char* event);
int __cdecl fcn_004e1ea0(char* event);
int __cdecl fcn_004e27b0(char* event);
int __cdecl fcn_004e2b40(char* event);
int __cdecl fcn_004e32c0(char* event);

/* Declaration only: complete allocation extent and storage owner remain unresolved. */
/* ADDRESS: GOLDTL 0x009b0840 */
/* ADDRESS: GOLD 0x0092c500 */
extern char g_9b0840[];

#endif
