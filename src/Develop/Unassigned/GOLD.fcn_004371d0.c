#include "Develop/Units/d3/d3_d3d.h"

void __cdecl fcn_00420140(unsigned int*, unsigned int*);
#define TEX_VTBL(t) (*(int**) (t))

/* ADDRESS: GOLD 0x004371d0 */
void __cdecl fcn_004371d0(void* tex, unsigned int* back)
{
	unsigned int ddsd_back[31];
	unsigned int ddsd2[31];
	unsigned int query[4];
	void* surf;
	unsigned char locked;
	char* x8;
	char* xc;

	surf = tex;
	locked = 0;
	if (surf == 0) {
		return;
	}
	query[0] = 0x401000;
	if (((int (__stdcall*)(void*, unsigned int*, void**)) TEX_VTBL(surf)[12])(surf, query, &tex) != 0) {
		return;
	}
	if (back == 0) {
		back = (unsigned int*) 0x7c;
		x8 = (char*) ddsd_back;
		__asm {
			mov edi, x8
			mov ebx, back
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
		ddsd_back[0] = 0x7c;
		d3d_LastResult = ((int (__stdcall*)(void*, int, void*, int, int)) TEX_VTBL(surf)[25])(surf, 0, ddsd_back, 1, 0);
		if (d3d_LastResult != 0) {
			d3d_LogResultError((char*) 0x5f944c, 0x30e, (char*) 0x5fa450);
		}
		locked = 1;
		back = ddsd_back;
	}
	x8 = (char*) 0x7c;
	xc = (char*) ddsd2;
	__asm {
		mov edi, xc
		mov ebx, x8
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
	ddsd2[0] = 0x7c;
	d3d_LastResult = ((int (__stdcall*)(void*, int, void*, int, int)) TEX_VTBL(tex)[25])(tex, 0, ddsd2, 1, 0);
	if (d3d_LastResult != 0) {
		d3d_LogResultError((char*) 0x5f944c, 0x316, (char*) 0x5fa418);
	}
	fcn_00420140(ddsd2, back);
	fcn_004371d0(tex, ddsd2);
	d3d_LastResult = ((int (__stdcall*)(void*, int)) TEX_VTBL(tex)[32])(tex, 0);
	if (d3d_LastResult != 0) {
		d3d_LogResultError((char*) 0x5f944c, 0x31b, (char*) 0x5fa3f4);
	}
	if (locked) {
		d3d_LastResult = ((int (__stdcall*)(void*, int)) TEX_VTBL(surf)[32])(surf, 0);
		if (d3d_LastResult != 0) {
			d3d_LogResultError((char*) 0x5f944c, 0x31e, (char*) 0x5fa3d4);
		}
	}
}
