#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

void* __cdecl gm_SearchTable67(int id);
float __cdecl gm_RandomFloat01(void);
unsigned short* __cdecl sim_StartEntityQueryByType(unsigned char* arg1);
void __cdecl fcn_004c6430(int a1, int a2, int a3);
void __cdecl fcn_004c6650(int a1);
int __cdecl fcn_004c5da0(int who, int key, int target, char* name, int mode, char* text);
void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);
int __cdecl fcn_00500cb0(void* a, void* b);
void __cdecl fcn_00546190(char* u);

/* ADDRESS: GOLDTL 0x00558220 */
void __cdecl fcn_00558220(char* obj)
{
	char* rec;
	char* e;
	void* q;
	int v;

	v = *(int*) (obj + 0x70);
	if (v < -2) {
		return;
	}
	if (v < 0) {
		fcn_00546190(obj);
		return;
	}
	if (v != 0) {
		return;
	}
	q = gm_SearchTable67(*(int*) (obj + 0xac));
	if (q == 0) {
		fcn_00546190(obj);
		return;
	}
	for (rec = (char*) 0x7f4ca4; (int) rec < (int) 0x85a0a4; rec += 0x21c) {
		if (*(unsigned char*) (rec + 4) > 0 && *(int*) (rec + 0x180) != 0 && *(void**) (rec + 0x168) == q && *(int*) (rec + 0x16c) != 0 && gm_RandomFloat01() > *(double*) 0x662908 && *(int*) (*(int*) (rec + 0x180) + 0x2c) == *(int*) (obj + 0xac)) {
			e = (char*) sim_StartEntityQueryByType((unsigned char*) *(int*) (rec + 0x16c));
			fcn_004c6430(*(int*) rec, 0, 0);
			fcn_004c6650(*(int*) rec);
			if (e != 0) {
				fcn_004c5da0(*(int*) rec, *(int*) (*(int*) (rec + 0x16c) + 1), *(int*) (e + 2), 0, 0, "Unkendunk");
			}
		}
	}
	*(pos14_7f4c00*) (obj + 0x52) = g_7f4c00;
	fcn_00500bb0(obj + 0x52, 0, 0x1e, 0);
	if (fcn_00500cb0(&g_7f4c00, obj + 0xb0) == 1) {
		fcn_00546190(obj);
	}
}
