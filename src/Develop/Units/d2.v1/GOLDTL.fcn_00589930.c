#include <string.h>
#include "client_types.h"

struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x25];
	int f5c;
	int f60;
	int f64;
	int f68;
	int f6c;
	char pad70[0x88];
};

struct act {
	int count;
	int item;
	int yes;
	int no;
	int amt[3];
};

extern pos14_7f4c00 g_7f4c00;
extern float g_662910;
extern float g_664150;

int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00526010(char*, int, char);
int __cdecl fcn_005898f0(void*);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_004c51a0(int, int, char, int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float,
                        int*);
int __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x00589930 */
void __cdecl fcn_00589930(char* a0)
{
	struct act act;
	struct msg m;
	char* p;
	int dlg;
	int lst;
	int btn;
	int i;
	int amt;
	int j;
	float f;

	act.count = gm_WalkEntityChain(*(unsigned short*) 0x774970);
	f = (float) act.count;
	act.amt[0] = (int) (f * g_662910);
	act.amt[1] = (int) (f * g_664150);
	act.amt[2] = (int) (f * *(float*) 0x6628ac);
	dlg = fcn_00470820(0, 0, (char*) 0x6a9514);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(*(int*) 0x772514);
	d2_SetForm(dlg, 2);
	i = fcn_0046fac0(0, 3, *(int*) 0x14b53a0, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + i * 0x2f4 + 0x6c) = 1;
	*(int*) (*(int*) 0x1015ea0 + i * 0x2f4 + 0x18) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c);
	fcn_00472900(i, 0x54);
	lst = fcn_004677e0(0x57, 0x14, 200, 0, 100, 0x7b, 2,
	                   *(int*) 0x772514);
	act.item = lst;
	fcn_00472380(lst, 0, 2, 0, 1);
	fcn_00468bb0(lst, 3, *(int*) 0x14b53a4, *(int*) 0x14b53a8,
	             *(int*) 0x14b53ac);
	d2_SetForm(dlg, 3);
	btn = fcn_00519190(0x4024);
	act.no = fcn_00472250(dlg, 3, btn);
	act.yes = fcn_00472250(dlg, 3, btn + 1);
	*(int*) 0x100f1dc = -1;
	do {
		j = fcn_00471f80(lst);
		d2_SetForm(dlg, 1);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x401e, 0x401c);
		amt = act.amt[j];
		fcn_00519190(0x401f, amt);
		if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		} else if (*(int*) 0x100f1dc != -1) {
			if (act.no == *(int*) 0x67d370) {
				if (fcn_00526010(
				        (char*) (0x7f4ca0 +
				                 (unsigned int) *(unsigned short*) 0x774970 *
				                     0x21c),
				        amt, *(char*) 0x773d75) &&
				    fcn_005898f0(a0)) {
					p = gm_GetEntityTableEntry(
					    (char*) (0x7f4ca0 +
					             (unsigned int) *(unsigned short*)
					                     0x774970 *
					                 0x21c));
					if (p)
						*(int*) (p + 0x28) += amt;
					fcn_004c51a0(
					    -1,
					    *(int*) (0x7f4ca4 +
					             (unsigned int) *(unsigned short*)
					                     0x774970 *
					                 0x21c),
					    *(char*) 0x773d75, amt);
					memset(&m, 0, sizeof(m));
					m.kind = 0x99;
					m.code = 2;
					m.f60 = -1;
					m.f64 = -1;
					m.f68 = 3;
					m.f6c = j;
					act.count = -1;
					m.owner = ((struct house*) 0x7f4ca0)[*(unsigned short*) (a0 + 0x27)].owner;
					m.target = *(int*) (a0 + 1);
					m.when = g_7f4c00;
					m.f5c = *(int*) (a0 + 1);
					fcn_004a5e60(
					    (unsigned short*) (0x7f4ca0 +
					                       (unsigned int) *(unsigned short*)
					                               0x774970 *
					                           0x21c),
					    0, 0x7b4c4a0, 0, 0.0f, 100.0f, &act.count);
					m.f60 = act.count;
					i = fcn_004c5530(&m);
					if (i != -1) {
						for (;;) {
							if (fcn_004c4450(i))
								break;
							fcn_005373e0(0, 0x20007);
						}
					}
					fcn_004c3030(-7, 0, (char*) 0x6a9508, 0);
					lst = act.item;
					*(int*) 0x774654 = 1;
				}
			} else if (act.yes == *(int*) 0x67d370) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) 0x589930, 0x677c7));
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
