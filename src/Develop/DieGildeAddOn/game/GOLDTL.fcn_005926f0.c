#include <windows.h>
#include <string.h>
#include "client_dialog_state.h"
extern int g_14ce8e0;

/* Globals referenced by the lobby setup.  The 0x779c60 status block and the
 * 0x7e23e2 INI image have no managed data rows yet, so they are addressed
 * directly; the pointer globals are declared with their evidenced types. */
extern unsigned* g_774a34;
extern int g_779c40;
extern char* g_779cb8;
extern int* g_779ce4;
extern void* g_1015ea0;
extern void* g_6a9b9c;

extern void* __cdecl fcn_00470820(int, int, char*);
extern void __cdecl fcn_00471b60(void*);
extern void __cdecl io_AppendText(int);
extern int __cdecl fcn_00471e30(void*);
extern int __cdecl fcn_00471f80(void*);
extern int __cdecl fcn_00472250(void*, int, int);
extern int __cdecl fcn_00472380(void*, char*);
extern int __cdecl d2_SetBildArgument(void*, int);
extern int __cdecl fcn_004727a0(void*, int);
extern int __cdecl fcn_00474cf0(void*);
extern int __cdecl fcn_00469e30(int);
extern int __cdecl fcn_00469e70(void);
extern int __cdecl fcn_004ce080(void);
extern int __cdecl fcn_004ce090(void);
extern void* __cdecl fcn_004ce180(void);
extern int __cdecl fcn_004ce1a0(void);
extern void* __cdecl fcn_004ce1c0(void);
extern int __cdecl fcn_004ce1d0(void);
extern int __cdecl fcn_004ce210(int);
extern int __cdecl fcn_004ce260(void);
extern int __cdecl fcn_004ce2a0(int, char*);
extern int __cdecl fcn_004ce320(void*);
extern int __cdecl fcn_004ce380(void*);
extern int __cdecl fcn_004c4450(int);
extern int __cdecl fcn_00507400(int, int);
extern int __cdecl fcn_00507b00(int);
extern int __cdecl fcn_0051af00(char*, int);
extern int __cdecl fcn_00526120(char*, int);
extern int __cdecl fcn_00535960(void);
extern int __cdecl fcn_005373e0(void*, int);
extern int __cdecl fcn_00593110(void);
extern int __cdecl fcn_005931a0(void);
extern int __cdecl fcn_00593200(void);
extern int __cdecl fcn_00593360(void);
extern int __cdecl fcn_005934d0(void);
extern int __cdecl fcn_00593550(void);
extern int __cdecl fcn_005936f0(int, int);
extern int __cdecl fcn_00593ff0(int);
extern int __cdecl fcn_005941e0(void);
extern int __cdecl fcn_0064d41a(char*, char*, int);

/* ADDRESS: GOLDTL 0x005926f0 */
int __cdecl fcn_005926f0(void)
{
	char v11[0x100];
	char v13[0x100];
	char v12[0x48];
	int ret = 0;
	int n;
	int flag;
	void* h;
	int d;

	fcn_004ce080();
	n = 0x57;
	/* Reviewed original fixed-EBX fill core, native 00592719..00592731;
	 * the destination immediate and homed count also match native. */
	__asm {
		mov edi, 0x779c60
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L_fill
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L_fill:
		add ecx, ebx
		rep stosb
	}
	g_774a34 = (unsigned*)0;
	g_779c40 = -1;
	g_779ce4 = (int*)fcn_004ce1c0();
	if (g_779ce4 == 0) {
		h = (void*)fcn_00470820(0, 0, (char*)0x68d714);
		fcn_00471b60(h);
		io_AppendText(0x87);
		(*(int*)0x100f1dc) = -1;
		do {
			if (g_14ce8e0 != 0 || *(char*)0x14cf950 == 1) {
				g_774654 = 1;
				fcn_00471e30(h);
				return 0;
			}
		} while (fcn_005373e0((void*)fcn_005926f0, 0x24087) != 0);
		fcn_00471e30(h);
		return 0;
	}

	GetPrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a1e54, (char*)0x6a401c, (char*)0x779c72, 0x20, (char*)0x7e22c0);
	GetPrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a1e3c, (char*)0x6a4010, (char*)0x779c82, 0x20, (char*)0x7e22c0);
	*(int*)0x779c6c = GetPrivateProfileIntA((char*)0x6a1e4c, (char*)0x6a4008, 0, (char*)0x7e22c0);
	*(unsigned char*)0x779c70 = (unsigned char)GetPrivateProfileIntA((char*)0x6a1e4c, (char*)0x6a3ffc, 0, (char*)0x7e22c0);
	*(unsigned char*)0x779c71 = (unsigned char)GetPrivateProfileIntA((char*)0x6a1e4c, (char*)0x6a3ff4, 0, (char*)0x7e22c0);
	*(unsigned char*)0x779c6b = (unsigned char)GetPrivateProfileIntA((char*)0x6a1e4c, (char*)0x6a9bb0, 0, (char*)0x7e22c0);
	d = fcn_00507b00(*(unsigned char*)0x779c6b);
	*(unsigned char*)0x779c6b = (unsigned char)fcn_00507400(d, 1);

	*(unsigned char*)0x7e23e2 = 0x10;
	*(unsigned char*)0x779c6a = 0x10;
	*(unsigned char*)0x779c97 = 0x46;
	*(unsigned char*)0x779c99 = 0x46;
	*(int*)0x779c92 = -1;
	*(unsigned char*)0x779c96 = 0x5a;
	*(unsigned char*)0x779c98 = 0x78;
	*(unsigned char*)0x779c9a = 0x5a;
	if (*(int*)0x9baadc == 0x7f) {
		*(unsigned char*)0x779c6b = *(unsigned char*)0x9badc0;
		*(unsigned char*)0x779c70 = *(unsigned char*)0x9badc4;
		*(unsigned char*)0x779c71 = *(unsigned char*)0x9badc8;
		*(int*)0x779c6c = *(int*)0x9badcc - 0x59a;
		strcpy((char*)0x779c72, (char*)0x9bada0);
		strcpy((char*)0x779c82, (char*)0x9badb0);
	}

	d = fcn_004ce320((void*)0x779c60);
	if (d == -1)
		return -1;
	while (fcn_004c4450(d) == 0)
		fcn_00535960();
	if (fcn_004c4450(d) == 2) {
		fcn_0051af00(v11, 0x88);
		fcn_00526120(v11, 0x100);
		return -1;
	}
	d = fcn_004ce1d0();
	if (d == -1)
		return -1;
	while (fcn_004c4450(d) == 0)
		fcn_00535960();
	fcn_00469e30(0x7d6);
	g_779cb8 = (char*)fcn_004ce1a0();
	if (g_779cb8 == 0) {
		h = (void*)fcn_00470820(0, 0, (char*)0x68d714);
		fcn_00471b60(h);
		io_AppendText(0x87);
		(*(int*)0x100f1dc) = -1;
		do {
			if (g_14ce8e0 != 0 || *(char*)0x14cf950 == 1) {
				g_774654 = 1;
				fcn_00471e30(h);
				return 0;
			}
		} while (fcn_005373e0((void*)fcn_005926f0, 0x24087) != 0);
		fcn_00471e30(h);
		return 0;
	}

	g_6a9b9c = (void*)fcn_00470820(0x3c, 0, (char*)0x6a9ba0);
	fcn_00471b60(g_6a9b9c);
	fcn_005931a0();
	fcn_00593110();
	fcn_00593200();
	fcn_005934d0();
	fcn_00593360();
	fcn_00593550();
	fcn_004727a0(g_6a9b9c, 1);
	h = (void*)fcn_00472250(g_6a9b9c, 0, 0);
	d2_SetBildArgument(h, 0x40);
	flag = 0;
	fcn_00472380(h, (char*)0x6b5c60);
	*(int*)((char*)g_1015ea0 + (int)h * 0x2f4 + 0x18) = 0x26c;
	*(int*)((char*)0x102d168 + *(int*)((char*)g_1015ea0 + (int)h * 0x2f4 + 0x88) * 0x220) |= 0x200;
	*(int*)((char*)0x102d150 + *(int*)((char*)g_1015ea0 + (int)h * 0x2f4 + 0x88) * 0x220) = 0x26c;
	*(int*)((char*)0x102d29c + *(int*)((char*)g_1015ea0 + (int)h * 0x2f4 + 0x88) * 0x220) = 0x26c;
	(*(int*)0x100f1dc) = -1;

	do {
		if (flag == 0) {
			if (*(int*)0x7725d0 != 0) {
				flag = 1;
			} else if (*(char*)0x14cf950 == 0x1c) {
				fcn_00474cf0(h);
				flag = 1;
			}
		} else {
			if (*(int*)0x7725d0 == 0 || *(char*)0x14cf950 == 0x1c) {
				flag = 0;
				strcpy(v12, (char*)fcn_00471f80(h));
				fcn_00472380(h, (char*)0x6b5c60);
				if (strlen(v12) != 0) {
					if (g_779c40 != -1)
						fcn_004ce2a0(g_779c40, v12);
					else
						fcn_004ce2a0(0, v12);
				}
			}
		}

		if (*(int*)0x14cbca0 == -1) {
			ret = -1;
			g_774654 = 1;
			goto next;
		}
		if (fcn_004ce090()) {
			g_774654 = 1;
			goto next;
		}
		if ((*(int*)0x100f1dc) != -1) {
			int key = *(int*)0x67d370;
			if (key == *(int*)0x6a9b98) {
				d = fcn_004ce260();
				while (fcn_004c4450(d) == 0)
					fcn_00535960();
				g_774654 = 1;
				ret = -1;
				goto last;
			}
			if (key == *(int*)0x6a9b90) {
				d = fcn_004ce210(*(int*)(g_779cb8 + 4) == 0);
				while (fcn_004c4450(d) == 0)
					fcn_00535960();
				*(int*)((char*)g_1015ea0 + *(int*)0x6a9b90 * 0x2f4 + 0x38) = *(int*)(g_779cb8 + 4);
				if (fcn_004ce090())
					g_774654 = 1;
			} else if (key == *(int*)0x6a9b94) {
				if (*(int*)(g_779cb8 + 4) != 0) {
					d = fcn_004ce210(0);
					while (fcn_004c4450(d) == 0)
						fcn_00535960();
					*(int*)((char*)g_1015ea0 + *(int*)0x6a9b90 * 0x2f4 + 0x38) = *(int*)(g_779cb8 + 4);
				}
				if (*(int*)(g_779cb8 + 4) == 0 && fcn_005936f0(0x24087, 1)) {
					strcpy((char*)0x779c72, (char*)0x7e23ea);
					strcpy((char*)0x779c82, (char*)0x7e240a);
					*(int*)0x779c6c = *(int*)0x7e23e4 - 0x59a;
					*(unsigned char*)0x779c70 = *(unsigned char*)0x7e23e8;
					*(unsigned char*)0x779c71 = *(unsigned char*)0x7e23e9;
					d = fcn_004ce380((void*)0x779c60);
					while (fcn_004c4450(d) == 0)
						fcn_00535960();
					if (fcn_00593ff0(0x24087)) {
						*(unsigned char*)0x779c6b = *(unsigned char*)0x7e23e3;
						d = fcn_004ce380((void*)0x779c60);
						while (fcn_004c4450(d) == 0)
							fcn_00535960();
					}
				}
			} else {
				int i;
				int sel = *(int*)0x779ce0;
				for (i = 0; i < *g_774a34; i++) {
					if (i != sel && key == ((int*)0x779cc0)[i])
						break;
				}
				if (i < *g_774a34) {
					int id = ((int*)0x779cc0)[i];
					*(int*)((char*)g_1015ea0 + id * 0x2f4 + 0x38) = (*(int*)((char*)g_1015ea0 + id * 0x2f4 + 0x38) == 0);
					if (*(int*)((char*)g_1015ea0 + id * 0x2f4 + 0x38) != 0)
						g_779c40 = g_774a34[i + 1];
					else
						g_779c40 = -1;
					if (i >= 0) {
						int k;
						for (k = 0; k < *g_774a34; k++) {
							if (i != k)
								*(int*)((char*)g_1015ea0 + ((int*)0x779cc0)[k] * 0x2f4 + 0x38) = 0;
						}
					}
				}
			}
		}
	next:
		(*(int*)0x100f1dc) = -1;
		if (*(int*)((char*)*(int*)0x779ce4 + 4) != 0) {
			if (fcn_004ce090()) {
				g_774654 = 1;
			} else {
				d = fcn_004ce1d0();
				while (fcn_004c4450(d) == 0)
					fcn_00535960();
				g_774a34 = (unsigned*)fcn_004ce180();
				fcn_00593360();
				fcn_00593550();
				fcn_005941e0();
				*(int*)((char*)*(int*)0x779ce4 + 4) = 0;
			}
		}
	last:
		;
	} while (fcn_005373e0((void*)fcn_005926f0, 0x24087) != 0);

	fcn_00471e30(g_6a9b9c);
	*(unsigned char*)0x7e23e2 = 0x12;
	*(unsigned char*)0x7e23e3 = *(unsigned char*)(g_779cb8 + 0xb);
	*(unsigned char*)0x7e23e8 = *(unsigned char*)(g_779cb8 + 0x10);
	*(unsigned char*)0x7e23e9 = *(unsigned char*)(g_779cb8 + 0x11);
	*(int*)0x7e23e4 = *(int*)(g_779cb8 + 0xc);
	strcpy((char*)0x7e240a, (char*)(g_779cb8 + 0x22));
	strcpy((char*)0x7e23ea, (char*)(g_779cb8 + 0x12));
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a1e54, (char*)0x7e23ea, (char*)0x7e22c0);
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a1e3c, (char*)0x7e240a, (char*)0x7e22c0);
	fcn_0064d41a(v13, (char*)0x6a81d8, *(int*)0x7e23e4);
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a4008, v13, (char*)0x7e22c0);
	fcn_0064d41a(v13, (char*)0x6a81d8, *(int*)0x7e23e8 & 0xff);
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a3ffc, v13, (char*)0x7e22c0);
	fcn_0064d41a(v13, (char*)0x6a81d8, *(int*)0x7e23e8 >> 8 & 0xff);
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a3ff4, v13, (char*)0x7e22c0);
	fcn_0064d41a(v13, (char*)0x6a81d8, *(unsigned char*)0x7e23e3);
	WritePrivateProfileStringA((char*)0x6a1e4c, (char*)0x6a9bb0, v13, (char*)0x7e22c0);
	fcn_00469e70();
	return ret;
}
