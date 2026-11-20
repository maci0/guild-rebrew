#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00445600(int, int, int, int*);
void __cdecl d3_TransformPoint(char*, char*, int*);
int __cdecl fcn_004fda30(int);
char* __cdecl ch_CreateAtPosition(char*, float*);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl fcn_004fdcf0(char*);
void __cdecl fcn_004fdfe0(char*);

/* ADDRESS: GOLDTL 0x004fe2e0 */
int __cdecl fcn_004fe2e0(char* a0, int a1, int* a2, int* a3, int a4, int* a5)
{
	int savedContext;
	float def[4];
	float opt[4];
	int* q;
	int* p;
	int v5;
	char* v6;

	savedContext = d3_CurrentContextIndex;
	def[0] = 0.0f;
	def[1] = 0.0f;
	def[2] = 0.0f;
	def[3] = 0.0f;
	p = a2;
	if (p == 0) {
		p = (int*) def;
	}
	q = a3;
	if (q == 0) {
		q = (int*) def;
	}
	if (a1 < 0) {
		return 0;
	}
	fcn_004432d0(a1, 1);
	if (a5 != 0) {
		v5 = fcn_00445600(a4, 0x100, 0, a5);
		if (v5 != 0) {
			d3_TransformPoint((char*) v5, (char*) v5 + 0x4c, (int*) opt);
			goto have;
		}
	}
	if (p == 0 && q == 0) {
		fcn_004432d0(savedContext, 1);
		return *(int*) (a0 + 0x184);
	}
	*(int*) &opt[0] = p[0];
	*(int*) &opt[1] = p[1];
	*(int*) &opt[2] = p[2];
have:
	v5 = fcn_004fda30(*(unsigned short*) a0);
	if (v5 != 0) {
		v6 = (char*) (v5 + 4);
		*(char**) (a0 + 0x184) = ch_CreateAtPosition(v6, opt);
		if (*(char**) (a0 + 0x184) != 0) {
			fcn_0064d41a(*(char**) (*(char**) (a0 + 0x184) + 0x34), g_68b0d8, *(int*) (a0 + 4));
			*(void**) (*(char**) (*(char**) (a0 + 0x184) + 0x34) + 0x204) = a0;
			*(int*) (*(char**) (*(char**) (a0 + 0x184) + 0x34) + 0x48) = *(unsigned short*) a0 | 0x3000000;
			if (a3 != 0) {
				d3_SetObjectRotation(*(char**) (*(char**) (a0 + 0x184) + 0x34), a3);
			}
			strcpy(a0 + 0x1f4, v6);
			fcn_004fdcf0(a0);
			fcn_004fdfe0(a0);
		}
	}
	fcn_004432d0(savedContext, 1);
	return *(int*) (a0 + 0x184);
}
