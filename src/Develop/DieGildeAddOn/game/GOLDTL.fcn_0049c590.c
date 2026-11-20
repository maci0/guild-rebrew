#include "Develop/DieGildeAddOn/game/entity_record.h"
/* Command handler for the entity selection dialog: reacts to the show (0x12)
 * and hide (0x0f) command of the dialog record and drives the GUI helpers. */
#include <math.h>

#pragma intrinsic(log10)

extern char g_7f4ca0[];
extern char g_773d75;
extern float g_1009b6c;
extern float g_1009b74;
extern float g_1009b7c;
extern float g_1009b8c;
extern float g_1009b94;
extern float g_1009b9c;

int __cdecl gm_StartFilteredEntitySearch(int a0, int a1, int a2);
int __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3, int a4);
void __cdecl fcn_004c4510(int a0, int a1);
void __cdecl fcn_004c4670(int a0, int a1, int a2, char* a3);
int __cdecl fcn_004c5360(void);
int __cdecl fcn_004c51a0(int a0, int a1, char a2, int a3);
void __cdecl fcn_004f5e20(int a0, int a1);
void __cdecl fcn_005b2150(int a0, char* a1, int a2, int a3, int a4);
void __cdecl fcn_005100f0(int a0, int a1);
void __cdecl fcn_005b21d0(int a0, char* a1, int a2);

/* ADDRESS: GOLDTL 0x0049c590 */
int __cdecl ai_RunAblassKaufen(int entityArg, char* purchaseReq, char* commandArg)
{
	int rec;
	int itemMatch;
	int computedAmount;
	unsigned char cmd;
	int n;

	if (*(unsigned char*) purchaseReq != 4) {
		return 0;
	}
	rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (purchaseReq + 4));
	if (rec == 0) {
		return 0;
	}
	if (*(unsigned short*) (rec + 0x27) == 0xffff) {
		return 0;
	}
	itemMatch = fcn_00502cd0(*(int*) (rec + 0x5d), 2, 6, 0, 0xf2);
	cmd = *(unsigned char*) commandArg;
	if (cmd == 0x12) {
		n = *(int*) (purchaseReq + 0x10);
		computedAmount = (int) (n / log10((double) n));
		fcn_004c4510(entityArg, *(int*) (entityArg + 4));
		fcn_004c4670(4, 1, 0x1ac, purchaseReq + 0x10);
		fcn_004c5360();
		fcn_004c51a0(-1, *(int*) (entityArg + 4), g_773d75,
		    *(int*) (purchaseReq + 0x10));
		fcn_004c51a0(*(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)]
			+ 4),
		    -1, g_773d75, computedAmount);
		fcn_004f5e20(*(int*) (entityArg + 4), (int) *(float*) (purchaseReq + 0x14));
		fcn_005b2150(entityArg,
		    (char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)],
		    rec, computedAmount, *(int*) (purchaseReq + 0x10));
		g_1009b8c = g_1009b6c * *(float*) (purchaseReq + 0x14);
		g_1009b94 = g_1009b74 * *(float*) (purchaseReq + 0x14);
		g_1009b9c = g_1009b7c * *(float*) (purchaseReq + 0x14);
		return 0x26;
	}
	if (cmd == 0x0f && itemMatch != 0) {
		fcn_004f5e20(*(int*) (entityArg + 4), (int) *(float*) (purchaseReq + 0x14));
		fcn_005100f0(*(int*) (entityArg + 4), -*(int*) (purchaseReq + 0x10));
		fcn_005100f0(*(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)]
			+ 4), 1);
		fcn_005b21d0(entityArg,
		    (char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)], rec);
		return 0x26;
	}
	return 0;
}
