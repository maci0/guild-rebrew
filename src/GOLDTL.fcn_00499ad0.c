

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time499a;
#pragma pack(pop)

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	Time499a at;
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
} Msg499a;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
} House499a;

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_6a375c;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5420(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(Time499a*, int, int, int);
void __cdecl fcn_004c5530(Msg499a*);

#pragma optimize("y", off)
int __cdecl fcn_00499ad0(char* e)
{
	Msg499a m;
	Time499a st;
	int ret;
	char* s;
	char* r;
	int i;
	int k;

	s = gm_StartFilteredEntitySearch(1, 5, 0xf);
	ret = 2;
	if (s == 0) {
		return 0;
	}
	r = fcn_00502cd0(*(int*) (s + 0x5d), 2, 6, 0, 0x115);
	if (r == 0) {
		return 0;
	}
	fcn_004c51a0(*(int*) (r + 2), *(int*) (e + 4), 0, 0x3e80);
	fcn_004c4510(e, *(int*) (e + 4));
	fcn_004c4570(1, 1, 0xd, &ret);
	fcn_004c5360();
	fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0, 0x4000);
	st = (*(Time499a*)&g_7f4c00);
	fcn_00500bb0(&st, gm_RandomMod(4) + 1, gm_RandomMod(8) * 7, 0);
	if (e[2] == 5) {
		i = 0;
		for (k = 0; k < 768; k++) {
			if (i >= g_6a375c) {
				break;
			}
			if (((House499a*)g_7f4ca0)[k].type == 6 || ((House499a*)g_7f4ca0)[k].type == 7) {
				{
					int dst;
					int n;

					n = sizeof(m);
					dst = (int) &m;
					__asm {
					mov edi, dst
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
				}
				m.owner = ((House499a*)g_7f4ca0)[k].owner;
				m.kind = 0x69;
				m.target = -1;
				m.code = 9;
				m.at = st;
				m.who = 2;
				m.other = *(int*) (e + 4);
				fcn_004c5530(&m);
				i++;
			}
		}
	}
	return 0x19;
}
