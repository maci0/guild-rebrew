#include "Develop/Units/d2.v1/d2_win.h"









// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern int g_100f1dc;
#include "client_dialog_state.h"

int __cdecl hst_ReadDueText(char* name, char* text);
int __cdecl d2_CreateScrollPerga(void);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl d2_UpdateScrollPerga(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_005355f0(void);

/* ADDRESS: GOLDTL 0x004b3490 */
void __cdecl fcn_004b3490(void)
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
	if (hst_ReadDueText(name, text) != 1) {
		return;
	}
	h = d2_CreateScrollPerga();
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	w = d2_CurrentWindowId;
	d2_SetForm(h, 2);
	io_AppendText(0x10b0);
	fcn_0046e830(-1, -1, d2_CurrentWindowId, w, 0x767);
	*(int*) &((D2_WIN*)g_1015f40)[w].pad3c[0x238] = 0x18;
	d2_SetForm(h, 1);
	io_AppendText((int) "$C%s", text);
	d2_SetForm(h, 3);
	io_AppendText((int) "$C$Z$[%s$]", name);
	g_100f1dc = -1;
	do {
		d2_UpdateScrollPerga();
		if (g_100f1dc == 2) {
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
			if (hst_ReadDueText(name, text) != 1) {
				g_774654 = 1;
			} else {
				d2_SetForm(h, 2);
				io_AppendText(0x10b0);
				fcn_0046e830(-1, -1, d2_CurrentWindowId, w, 0x767);
				*(int*) &((D2_WIN*)g_1015f40)[w].pad3c[0x238] = 0x18;
				d2_SetForm(h, 1);
				io_AppendText((int) "$C%s", text);
				*(int*) &((D2_WIN*)g_77255c)->pad3c[0x21c] = 0;
				((D2_WIN*)g_77255c)->pad3c[0x234] = 2;
				d2_SetForm(h, 3);
				io_AppendText((int) "$C$Z$[%s$]", name);
			}
		}
	} while (main_RunFrameLoop(fcn_004b3490, 0x66087) != 0);
	fcn_005355f0();
}
