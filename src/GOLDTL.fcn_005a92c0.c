// FUNCTION: GOLDTL 0x005a92c0
// SIZE: 979

typedef struct {
	short s[7];
} Stamp5a92;
// SIZE 0xe

typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[0x214];
} Ent5a92;
// SIZE 0x21c

typedef struct {
	char b[0x2f4];
} Row5a92;
// SIZE 0x2f4

extern char g_7f4ca0[];
extern unsigned short g_774970;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern trade_868080 g_868080[];
extern unsigned char g_6a375c;
extern char g_6aae78[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl gm_AccumulateTyped2(Ent5a92*);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00526010(Ent5a92*, int, unsigned char);
int __cdecl fcn_005809f0(void);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00500bb0(Stamp5a92*, int, int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a92c0(char* p)
{
	Ent5a92* ent;
	char* q;
	int h;
	int ok;
	int n;
	int i;
	Stamp5a92 st;

	ent = &((Ent5a92*)g_7f4ca0)[g_774970];
	n = gm_AccumulateTyped2(ent);
	q = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	ok = 0;
	if (n < 0x3e80) {
		char text[0x100];

		fcn_0051af00(text, 0x1a00);
		fcn_00526120(text, ok);
		fcn_00532ef0();
		return;
	}
	h = fcn_00470820(0, 0, g_6aae78);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(0x19fe, ent->id, 0x3e80, &((Row5a92*)g_868080)[g_773d75]);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2 && fcn_00526010(ent, 0x3e80, g_773d75) != 0) {
				char msg[0xf8];
				char text[0x200];

				n = 0;
				{
					char* fdest;
					int flen;

					flen = sizeof(msg);
					fdest = msg;
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
				}
				*(int*) (msg + 8) = ent->f4;
				msg[4] = 0x69;
				*(int*) (msg + 0xc) = -1;
				msg[0x36] = 9;
				*(Stamp5a92*) (msg + 0x28) = (*(Stamp5a92*)&g_7f4c00);
				if (fcn_005809f0() == 0) {
					fcn_00500bb0((Stamp5a92*) (msg + 0x28), 0, 5, 0);
				} else {
					fcn_00500bb0((Stamp5a92*) (msg + 0x28), fcn_0042e410(3) + 1, 0, 0);
				}
				st = *(Stamp5a92*) (msg + 0x28);
				msg[0x58] = 2;
				*(int*) (msg + 0x5c) = ent->f4;
				fcn_004c5530(msg);
				for (i = 0; i < 768 && n < g_6a375c; i++) {
					if ((((Ent5a92*)g_7f4ca0)[i].b2 == 6 || ((Ent5a92*)g_7f4ca0)[i].b2 == 7) && &((Ent5a92*)g_7f4ca0)[i] != ent) {
						{
							char* fdest;
							int flen;

							flen = sizeof(msg);
							fdest = msg;
							__asm {
								mov edi, fdest
								mov ebx, flen
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
						*(int*) (msg + 8) = ((Ent5a92*)g_7f4ca0)[i].f4;
						msg[4] = 0x69;
						*(int*) (msg + 0xc) = -1;
						msg[0x36] = 9;
						*(Stamp5a92*) (msg + 0x28) = st;
						msg[0x58] = 2;
						*(int*) (msg + 0x5c) = ent->f4;
						fcn_004c5530(msg);
						n++;
					}
				}
				fcn_004c51a0(*(int*) (q + 2), ent->f4, 0, 0x3e80);
				fcn_004c5420(ent->f4, 0x1c8, 4, 0, 0x4000);
				fcn_0051af00(text, 0x19ff);
				fcn_0057e880(0x2e, 0, 0, 0);
				ok = 1;
				fcn_00526120(text, 0);
			}
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005a92c0, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_00532ef0();
	if (ok) {
		fcn_0057e880(0x2e, 0, 1, 0);
	}
}
