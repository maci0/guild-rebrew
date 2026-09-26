// FUNCTION: GOLD 0x53f760
// SIZE: 175
// FUNCTION: GOLDTL 0x005475c0
// SIZE: 175

// SIZE 0x14
typedef struct {
	int tag;
	int a;
	int id;
	int b;
	int c;
} Msg;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_6a58ac[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c68c0(Msg* msg);

void __cdecl fcn_005475c0(void)
{
	char* e;
	char* w;

	for (e = gm_StartFilteredEntitySearch(1, 5, 0x16); e != 0; e = gm_AddObjekt()) {
		w = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x120);
		if (w == 0) {
			continue;
		}
		w = fcn_00502cd0(*(int*) (w + 0x14), 1, 0, 0x12c);
		if (w == 0) {
			continue;
		}
		if ((*(int*)&g_7f4c00) - *(int*) (w + 0x28) > 1) {
			Msg msg;

			msg.tag = 0x636c6572;
			msg.id = *(int*) (e + 1);
			msg.a = -1;
			msg.b = -1;
			fcn_004c4eb0(g_6a58ac);
			fcn_004c68c0(&msg);
			fcn_004c4ef0(g_6a58ac);
		}
	}
}
