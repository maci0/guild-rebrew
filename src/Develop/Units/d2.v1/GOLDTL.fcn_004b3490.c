typedef struct Win {
	char pad0[0x258];
	int x258;
	char pad25c[0x14];
	char x270;
	char pad271[3];
	int style;
	char pad278[0x3cc - 0x278];
} Win;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_772514;
extern char* g_77255c;
extern int g_100f1dc;
extern int g_774654;

int __cdecl fcn_004b33c0(char* name, char* text);
int __cdecl fcn_00535570(void);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl fcn_00535630(void);
int __cdecl fcn_005373e0(void*, int);
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
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
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
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
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
	if (fcn_004b33c0(name, text) != 1) {
		return;
	}
	h = fcn_00535570();
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	w = g_772514;
	d2_SetForm(h, 2);
	io_AppendText(0x10b0);
	fcn_0046e830(-1, -1, g_772514, w, 0x767);
	((Win*)g_1015f40)[w].style = 0x18;
	d2_SetForm(h, 1);
	io_AppendText((int) "$C%s", text);
	d2_SetForm(h, 3);
	io_AppendText((int) "$C$Z$[%s$]", name);
	g_100f1dc = -1;
	do {
		fcn_00535630();
		if (g_100f1dc == 2) {
			{
				char* p;
				int len;

				len = sizeof(text);
				p = text;
				/* block-fill prelude, see docs/codegen-walls.md section 6b */
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
				/* block-fill prelude, see docs/codegen-walls.md section 6b */
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
			if (fcn_004b33c0(name, text) != 1) {
				g_774654 = 1;
			} else {
				d2_SetForm(h, 2);
				io_AppendText(0x10b0);
				fcn_0046e830(-1, -1, g_772514, w, 0x767);
				((Win*)g_1015f40)[w].style = 0x18;
				d2_SetForm(h, 1);
				io_AppendText((int) "$C%s", text);
				((Win*)g_77255c)->x258 = 0;
				((Win*)g_77255c)->x270 = 2;
				d2_SetForm(h, 3);
				io_AppendText((int) "$C$Z$[%s$]", name);
			}
		}
	} while (fcn_005373e0(fcn_004b3490, 0x66087) != 0);
	fcn_005355f0();
}
