#include "Develop/Units/d2.v1/d2_win.h"









// SIZE 0x3cc

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl hst_ReadNextChronicleEntry(char* name, char* text, int arg);
int __cdecl d2_CreateScrollPerga(void);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
void __cdecl d2_UpdateScrollPerga(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyScrollPerga(void);

/* ADDRESS: GOLDTL 0x004b3810 */
void __cdecl d2_ShowHistoryScrollDialog(int arg)
{
	char text[0x1fb8];
	char name[0x100];
	int h;
	int w;

	{
		char* p;
		int len;

		len = sizeof(name);
		p = name;
		/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
	}
	{
		char* p;
		int len;

		len = sizeof(text);
		p = text;
		/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	if (hst_ReadNextChronicleEntry(name, text, arg) != 1) {
		return;
	}
	h = d2_CreateScrollPerga();
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	w = d2_CurrentWindowId;
	d2_SetForm(h, 2);
	io_AppendText(0x10b0);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, w, 0x767);
	*(int*) &((D2_WIN*)d2_Windows)[w].pad3c[0x238] = 0x18;
	d2_SetForm(h, 1);
	io_AppendText((int) "$C%s", text);
	d2_SetForm(h, 3);
	io_AppendText((int) "$C$Z$[%s$]", name);
	d2_DialogButtonAction = -1;
	do {
		d2_UpdateScrollPerga();
		if (d2_DialogButtonAction == 2) {
			{
				char* p;
				int len;

				len = sizeof(text);
				p = text;
				/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
				__asm {
					mov edi, p
					mov ebx, len
					xor eax, eax
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L3
					rep stosb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep stosd
				L3:
					add ecx, ebx
					rep stosb
				}
			}
			{
				char* p;
				int len;

				len = sizeof(name);
				p = name;
				/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
				__asm {
					mov edi, p
					mov ebx, len
					xor eax, eax
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L4
					rep stosb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep stosd
				L4:
					add ecx, ebx
					rep stosb
				}
			}
			if (hst_ReadNextChronicleEntry(name, text, arg) != 1) {
				d2_DialogCloseRequested = 1;
			} else {
				d2_SetForm(h, 2);
				io_AppendText(0x10b0);
				d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, w, 0x767);
				*(int*) &((D2_WIN*)d2_Windows)[w].pad3c[0x238] = 0x18;
				d2_SetForm(h, 1);
				io_AppendText((int) "$C%s", text);
				*(int*) &((D2_WIN*)d2_CurrentWindow)->pad3c[0x21c] = 0;
				((D2_WIN*)d2_CurrentWindow)->pad3c[0x234] = 2;
				d2_SetForm(h, 3);
				io_AppendText((int) "$C$Z$[%s$]", name);
			}
		}
	} while (main_RunFrameLoop(d2_ShowHistoryScrollDialog, 0x66087) != 0);
	d2_DestroyScrollPerga();
}
