// FUNCTION: GOLD 0x005a1060
// SIZE: 229
// FUNCTION: GOLDTL 0x005aa390
// SIZE: 229

typedef struct {
	char b[0x21c];
} Ent5aa3;
// SIZE 0x21c

extern Ent5aa3 g_7f4ca0[];
extern unsigned short g_774970;
extern int g_14aad38;
extern int g_14aac9c;
extern char g_7d4190[];

int __cdecl fcn_004eb260(Ent5aa3* e);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00525f60(Ent5aa3* e, int);
void __cdecl fcn_005aa120(void);
void __cdecl fcn_005bdc30(int, char*, int, void (__cdecl*)(void), int);

#pragma optimize("y", off)
void __cdecl fcn_005aa390(void)
{
	char buf[0x50];
	char* fdest;
	int flen;
	int r;

	r = fcn_004eb260(&g_7f4ca0[g_774970]);
	if (r != 1) {
		if (r == -1) {
			fcn_00526120(g_14aad38, 0);
			return;
		}
		fcn_00525f60(&g_7f4ca0[g_774970], 5);
		return;
	}
	flen = 0x50;
	fdest = buf;
	__asm {
		mov edi, fdest
		mov ebx, flen
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
	*(int*) (buf + 0) = 1;
	*(int*) (buf + 4) = -1;
	*(int*) (buf + 0x10) = 6;
	*(char**) (buf + 8) = g_7d4190;
	*(int*) (buf + 0xc) = 1;
	*(int*) (buf + 0x4c) = 0x727;
	fcn_005bdc30(1, buf, g_14aac9c, fcn_005aa120, 0);
}
#pragma optimize("", on)
