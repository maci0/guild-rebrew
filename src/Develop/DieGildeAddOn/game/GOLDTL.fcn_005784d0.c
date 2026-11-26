#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_GetCommandStatus(int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl ch_StartMovement(unsigned int, unsigned int, int, int, int, char*);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_AssignActionSlot(int, int, int, int);
void __cdecl he_FreeAction(char*);
void __cdecl he_NotifyHeimsuchung(char*, char*, char*);


/* Runs the plague-heimsuchung action message through its states and updates
 * the action duration it reports back to the caller. */
/* ADDRESS: GOLDTL 0x005784d0 */
void __cdecl he_RunHeimsuchung(char* obj)
{
	unsigned short* lager;
	int state;
	int h;
	int res;

	lager = (unsigned short*) gm_LookupEntityRecordById(*(int*) (obj + 0xb4));
	if (lager == 0) {
		he_FreeAction(obj);
		return;
	}
	state = *(int*) (obj + 0x70);
	if (state == -1 || state == -2) {
		he_AssignActionSlot(0, 0, *lager, (int) obj);
		he_FreeAction(obj);
		return;
	}
	if (*(unsigned char*) (obj + 0x78) & 4) {
		return;
	}
	h = *(int*) (obj + 0x84);
	if (h != -1 && cm_GetCommandStatus(h) == 0) {
		return;
	}
	state = *(int*) (obj + 0x70);
	*(int*) (obj + 0x84) = -1;
	switch (state) {
	case 0:
		if (cm_GetCommandStatus(-1) == 0) {
			return;
		}
		he_AssignActionSlot(0, 0, *lager, (int) obj);
		res = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac));
		if (res == 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
			return;
		}
		*(int*) (obj + 0xbc) = ch_StartMovement(*(unsigned int*) &lager[2],
			*(unsigned int*) (res + 1), -1, 0, 1, "HEIMSUCHUNG");
		fcn_004c5620(2, obj);
		return;
	case 2:
		*(int*) (obj + 0xbc) = -1;
		if (*(int*) (*(int*) &lager[0xc2] + 0x128) != 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			gm_AddTime(obj + 0x52, 0, 4, 0);
			*(int*) (obj + 0x84) = fcn_004c5620(2, obj);
			return;
		}
		if (gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac)) != 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			h = (int) gm_LookupEntityRecordById(*(int*) (obj + 0xb0));
			if (h != 0) {
				gm_AddTime(obj + 0x52, 0x18, 0, 0);
				he_NotifyHeimsuchung(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (obj + 8)]),
					(char*) h, obj + 0x52);
			}
			*(int*) (obj + 0x84) = fcn_004c5620(3, obj);
			return;
		}
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
		return;
	case 3:
		if (*(int*) &lager[0xb6] == 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
			return;
		}
		*(int*) (obj + 0xbc) = ch_StartMovement(*(unsigned int*) &lager[2],
			*(unsigned int*) (*(int*) &lager[0xb6] + 1), -1, 0, 0, "HEIMSUCHUNG");
		*(int*) (obj + 0x84) = fcn_004c5620(4, obj);
		return;
	case 4:
		if (*(int*) &lager[0xb6] == 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
			return;
		}
		if (*(int*) (*(int*) &lager[0xc2] + 0x128) != 0) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			gm_AddTime(obj + 0x52, 0, 4, 0);
			return;
		}
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		he_AssignActionSlot(0, 0, *lager, 0);
		*(int*) (obj + 0x84) = fcn_004c5620(5, obj);
		h = *(int*) (obj + 0xb8) >> 1;
		if (h < 1) {
			h = 1;
		}
		*(int*) (obj + 0x52) = *(int*) (obj + 0x52) + h + 1;
		return;
	case 5:
		*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
		return;
	}
}
