#ifndef CLIENT_D3_DIALOG_H
#define CLIENT_D3_DIALOG_H

#include <windows.h>

/* Inferred argument-slot names; non-owning views with unknown backing storage. */
/* ADDRESS: GOLD 0x00631224 */
extern char DialogArgument4;
/* ADDRESS: GOLD 0x00631218 */
extern int DialogArgument5;
/* ADDRESS: GOLD 0x0063121c */
extern int DialogArgument1;

BOOL __stdcall fcn_0041c830(HWND a1, UINT a2, WPARAM a3, LPARAM a4);
void __cdecl fcn_0041cf60(int a, int unused, HWND owner, char flag, int context);

#endif
