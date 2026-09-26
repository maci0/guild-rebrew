#pragma pack(push, 1)
// SIZE 0xa9
typedef struct {
	unsigned char kind;
	int id;
	char pad5[0xa4];
} Player_551f90;

// SIZE 0x24d
typedef struct {
	char type;
	char pad1[0x24c];
} Kind_551f90;
#pragma pack(pop)

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp_551f90;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x214];
} Entity_551f90;

// SIZE 0xd4
typedef struct {
	char pad0[0x52];
	Stamp_551f90 stamp;
	char pad60[0x24];
	int event;
	char pad88[0x24];
	int who;
	int rnd;
	int value;
	char padb8[4];
	int ev[4];
	char padcc[4];
	int player;
} Order_551f90;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_90e094;
extern unsigned char* g_868050;
extern int g_6643d8[];
extern char g_7f4ca0[];

unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c5620(int, Order_551f90*);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, const char*);
void __cdecl fcn_00500bb0(Stamp_551f90*, int, int, int);
void __cdecl fcn_005b2790(void);

// FUNCTION: GOLDTL 0x551f90
// SIZE: 652

void __cdecl fcn_00551f90(Order_551f90* o)
{
	char m[0xf8];
	char* fill;
	int n;
	Player_551f90* p;
	int i;

	o->stamp = (*(Stamp_551f90*)&g_7f4c00);
	n = 0x100;
	i = fcn_0042e410(0x100);
	do {
		p = &((Player_551f90*)g_90e094)[i];
		if (((Kind_551f90*)g_868050)[p->kind].type == 7) {
			o->rnd = fcn_0042e410(0x100);
			o->value = g_6643d8[fcn_0042e410(0x10)];
			n = sizeof(m);
			fill = m;
			/* align-up block fill: no msvc6 C spelling emits it
			 * (docs/codegen-walls.md 6b) */
			__asm {
				mov edi, fill
				mov ebx, n
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
			*(int*) (m + 0x58) = p->id;
			*(int*) (m + 0x5c) = p->id;
			*(int*) (m + 0x64) = o->rnd;
			*(int*) (m + 0x68) = o->value;
			*(int*) (m + 0x60) = -1;
			*(int*) (m + 0x6c) = o->who;
			*(int*) (m + 0xc) = -1;
			m[4] = 0x78;
			m[0x36] = 9;
			*(Stamp_551f90*) (m + 0x28) = (*(Stamp_551f90*)&g_7f4c00);
			for (i = 0; i < 0x300; i++) {
				if (((Entity_551f90*)g_7f4ca0)[i].type == 6 || ((Entity_551f90*)g_7f4ca0)[i].type == 7) {
					*(int*) (m + 8) = ((Entity_551f90*)g_7f4ca0)[i].id;
					fcn_004c5530(m);
				}
			}
			o->ev[0] = fcn_004c64b0(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[1] = fcn_004c64b0(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[2] = fcn_004c64b0(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->ev[3] = fcn_004c64b0(0xe, p->id, -1, 0x12, 0, 0, "PEST");
			o->player = p->id;
			fcn_00500bb0(&o->stamp, 0, 1, 0);
			o->event = fcn_004c5620(0, o);
			fcn_005b2790();
			return;
		}
		n--;
		i = (i + 1) % 256;
	} while (n != 0);
	o->event = fcn_004c5620(-1, o);
}
