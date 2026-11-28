int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;



void __cdecl amt_RetireExpiredRulers(void);
void __cdecl amt_SpawnHistoricalOfficeHolders(void);
void __cdecl amt_NominateSpecialOfficeCandidates(void);
void __cdecl amt_VacateSpecialOffice(void);
void __cdecl amt_AssignSpecialOffices(void);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl sim_SetSyncParams(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDDE 0x00561900 */
void __cdecl he_RunSpecialOffices(char* o)
{
	if (o[0x78] & 4) {
		return;
	}
	switch (*(int*) (o + 0x70)) {
	case 0:
		amt_RetireExpiredRulers();
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 2, 0, 0);
		cm_SendSetHE(1, o);
		break;
	case 1:
		amt_SpawnHistoricalOfficeHolders();
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 2, 0, 0);
		cm_SendSetHE(2, o);
		break;
	case 2:
		amt_NominateSpecialOfficeCandidates();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 0x16, 0, 0);
		cm_SendSetHE(3, o);
		break;
	case 3:
		amt_VacateSpecialOffice();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 6, 5, 0);
		((pos14_7f4c00*) (o + 0x52))->a++;
		cm_SendSetHE(4, o);
		break;
	case 4:
		amt_AssignSpecialOffices();
		sim_SetSyncParams((pos14_7f4c00*) (o + 0x52), 0xa, 0, 0);
		cm_SendSetHE(0, o);
		break;
	}
}
