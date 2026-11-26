#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_7f4ca0[];
extern pos14_7f4c00 gm_GameTime;

int __cdecl fcn_004a5fe0(char*, int, int, int, int, int, int, int*);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_FreeAction(char*);
int __cdecl fcn_004c5620(char, unsigned char*);

/* ADDRESS: GOLDTL 0x00578e10 */
void __cdecl fcn_00578e10(char* action)
{
	int flag;
	int zero;
	int n;
	char* rec;

	flag = 4;
	zero = 0;
	if ((*(unsigned char*) (action + 0x78) & flag) != 0) {
		return;
	}
	rec = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (action + 8)]);
	n = fcn_004a5fe0(rec,
	    5, flag, zero, zero, zero, 5, (int*) (action + 0xb4));
	if (n == 0) {
		he_FreeAction(action);
		return;
	}
	if (n < 5) {
		*(int*) (action + 0xb4 + n * 4) = 0;
	}
	*(int*) (action + 0xb0) = 0;
	*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
	gm_AddTime(action + 0x52, 0, 1, 0);
	*(int*) (action + 0x84) = fcn_004c5620(0, (unsigned char*) action);
}
