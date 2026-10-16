#ifndef EVENT_CALLBACKS_H
#define EVENT_CALLBACKS_H

/* Inferred validator contract and declaration home; the event remains a byte view. */
typedef int (__cdecl* EVENT_CHECK)(char* event);
typedef void (__cdecl* EVENT_RUN)(char* event);

/* First-slot call contract is reconstructed; second/third phase contracts remain open. */
void __cdecl fcn_004e7160(int kind, EVENT_RUN first, void* second, void* third,
    EVENT_CHECK check, unsigned char flag);

void __cdecl fcn_004e1920(char* event);
void __cdecl fcn_004da690(char* event);
void __cdecl fcn_004dcf50(char* event);
void __cdecl fcn_004d77e0(char* event);
void __cdecl fcn_004e0620(char* event);
void __cdecl fcn_004e1b00(char* event);
void __cdecl fcn_004e2090(char* event);
void __cdecl fcn_004e2890(char* event);
void __cdecl fcn_004e2b70(char* event);
void __cdecl fcn_004e3020(char* event);
void __cdecl fcn_004e33a0(char* event);
void __cdecl fcn_004e4180(char* event);

/* Reconstructed court decision callback; other phase-slot contracts remain open. */
void __cdecl fcn_004df1b0(char* participant, int* action);

/* Existing event helpers use word and unsigned-byte access views. */
void __cdecl fcn_004e5a00(int* event);
void __cdecl fcn_004e4f10(int* event);
int __cdecl cut_CutsceneReady(int* event);
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
