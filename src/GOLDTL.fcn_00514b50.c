// FUNCTION: GOLDTL 0x00514b50
// SIZE: 419

#include <stdlib.h>
#include <windows.h>

// SIZE 0x21c
typedef struct {
	short slot;
	unsigned char type;
	char pad3[0x161];
	unsigned char trade;
	char pad165[0x21c - 0x165];
} Entity;

// SIZE 0x2f4
typedef struct {
	char pad0[0x48];
	signed char count;
	char pad49[0x2f4 - 0x49];
} Variant;

#pragma pack(push, 1)
// SIZE 0x6
typedef struct {
	char pad0[2];
	int id;
} Unit;

// SIZE 0x61
typedef struct {
	char pad0[0x5d];
	int home;
} Player;
#pragma pack(pop)

extern int g_14cbca0;
extern int g_7747e8;
extern Entity g_7f4ca0[768];
extern Variant g_868060[];
extern unsigned char g_6a375c;
extern signed char g_7747b0;
extern char g_773d75;

void __cdecl fcn_00511580(int);
void __cdecl fcn_0053abe0(int);
void __cdecl fcn_00511900(int, int, int*);
void __cdecl fcn_00512ee0(void);
Player* __cdecl fcn_0050e4a0(int);
Unit* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);

int __cdecl fcn_00514b50(int variant)
{
	int wares[8];
	int* p;
	int i;
	int j;
	int k;
	Player* pl;
	Unit* u;

	if (g_14cbca0 == -1) {
		srand(timeGetTime());
	}
	fcn_00511580(0);
	if (g_7747e8 != 0) {
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].type == 6) {
				fcn_0053abe0(i);
				break;
			}
		}
	}
	k = variant;
	if (g_868060[k].count - g_6a375c > 0) {
		wares[0] = 0x18;
		wares[1] = 0x27;
		wares[2] = 0x33;
		wares[3] = 0x3f;
		wares[4] = 0x45;
		wares[5] = 0x4b;
		wares[6] = 0x12;
		wares[7] = 6;
		if (g_7747b0 & 0x80) {
			p = wares;
			variant = sizeof(wares);
			/*
			 * The reference zero-fills with the hand-written block-fill
			 * prelude no msvc6 C spelling emits (docs/codegen-walls.md 6b).
			 */
			__asm {
				mov edi, p
				mov ebx, variant
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
			wares[0] = 0x12;
		} else {
			for (i = 0; i < 768; i++) {
				if (g_7f4ca0[i].type == 6 || g_7f4ca0[i].type == 7) {
					for (j = 0; j < 8; j++) {
						if (g_7f4ca0[i].trade == wares[j]) {
							wares[j] = 0;
							break;
						}
					}
				}
			}
		}
		fcn_00511900(g_868060[k].count - g_6a375c, 8, wares);
	}
	fcn_00512ee0();
	pl = fcn_0050e4a0(1);
	if (pl != 0) {
		u = fcn_00502cd0(pl->home, 2, 6, 0, 0x115);
		if (u != 0) {
			fcn_004c51a0(u->id, -1, g_773d75, 0x75300);
		}
	}
	return 1;
}
