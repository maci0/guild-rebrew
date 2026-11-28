#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/client_types.h"

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern pos14_7f4c00 gm_GameTime;
extern char* g_14b5304;

int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
int __cdecl cm_SendSetHE(int, char*);
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl gm_ApplyAssassinDamage(char*, char*, int);
int __cdecl gm_RecordAssassinEvidence(char*, char*, int);
int __cdecl gm_GetElapsedMinutes(char*, char*);
int __cdecl ch_StartMovement(int, int, int, char*, int, char*);
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl cm_SendCancelCharacterActions(int);
int __cdecl he_TryTriggerAction0x9b(int, char*);
char* __cdecl he_FindNearestAction0x18(char*, char*, int);
int __cdecl he_RunSpyKillerCheck(char*, char*, char*);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl ai_FindEntityInFavorRange(unsigned short*, int, int, int, float, float, int*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x00576c90 */
void __cdecl he_RunAssassinAction(char* e)
{
	char text[0x100];
	char* h;
	char* p;
	char* q;
	char* r;
	int n;
	int c;

	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		goto state_minus;
	}
	if (*(unsigned char*) (e + 0x78) & 4) {
		return;
	}
	if (*(int*) (e + 0x84) != -1 && cm_GetCommandStatus(*(int*) (e + 0x84)) == 0) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	h = ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 8)]);
	switch (*(int*) (e + 0x70)) {
	case 0:
		if (cm_GetCommandStatus(*(int*) (e + 0xcc)) != 1) {
			goto minus_one;
		}
		p = cm_GetCommandResult(*(int*) (e + 0xcc));
		if (p == 0) {
			goto minus_one;
		}
		*(int*) (e + 0xb8) = *(int*) (p + 4);
		if (*(int*) (e + 0xbc) == 3) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(6, e);
			goto done;
		}
		r = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
		if (r == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		minus_one:
			*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
			goto done;
		}
		*(int*) (e + 0xcc) = ch_StartMovement(*(int*) (p + 4), *(int*) (r + 1), -1, 0, 1, (char*) 0x6a7e18);
		cm_SendSetHE(1, e);
		goto done;
	case 1:
		*(int*) (e + 0xcc) = -1;
		p = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			goto minus_one;
		}
		if (*(char**) (*(char**) (p + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 4, 0);
			goto done;
		}
		if (gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac)) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 1, 0, 0);
			*(int*) (e + 0x84) = cm_SendSetHE(3, e);
			goto done;
		}
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		goto minus_one;
	case 3:
		p = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			goto minus_one;
		}
		q = gm_LookupEntityRecordById(*(int*) (e + 0xb4));
		r = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb0));
		if (h != 0 && q != 0 && r != 0) {
			switch (*(int*) (e + 0xbc)) {
			case 1:
				if (gm_ApplyAssassinDamage(h, q, *(int*) (e + 0xc0)) != 0) {
					io_FormatTextBuffer(text, (char*) 0x4004, *(unsigned short*) q);
					he_PostEntityMessage(*(int*) (h + 4), -1, text, 1, 0x5fa, (char*) 0x6a7e78);
					io_FormatTextBuffer(text, (char*) 0x4006, *(int*) (e + 0xc0) + 0x4007);
					he_PostEntityMessage(*(int*) (q + 4), -1, text, 1, 0x5fb, (char*) 0x6a7e60);
				} else {
					io_FormatTextBuffer(text, (char*) 0x4005, *(unsigned short*) q);
					he_PostEntityMessage(*(int*) (h + 4), -1, text, 1, 0x5fa, (char*) 0x6a7e48);
					io_FormatTextBuffer(text, (char*) 0x400a);
					he_PostEntityMessage(*(int*) (q + 4), -1, text, 1, 0x5fb, (char*) 0x6a7e60);
				}
				break;
			case 2:
				if (gm_RecordAssassinEvidence(h, q, *(int*) (e + 0xc0)) != 0) {
					io_FormatTextBuffer(text, (char*) 0x4019, (char*) 0x400c, *(unsigned short*) q, *(unsigned short*) q);
					he_PostEntityMessage(*(int*) (h + 4), -1, text, 1, 0x5fa, 0);
				} else {
					io_FormatTextBuffer(text, (char*) 0x401a, (char*) 0x400c, *(unsigned short*) q, *(unsigned short*) q);
					he_PostEntityMessage(*(int*) (h + 4), -1, text, 1, 0x5fa, 0);
				}
				break;
			case 3:
				*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
				*(int*) (e + 0xc4) = -1;
				*(int*) (e + 0xc8) = 0;
				*(int*) (e + 0x84) = cm_SendSetHE(6, e);
				*(int*) (e + 0x84) = cm_SendSetHE(4, e);
				goto done;
			case 4:
				he_TryTriggerAction0x9b(*(int*) (r + 1), q);
				break;
			}
		}
		*(int*) (e + 0x84) = cm_SendSetHE(4, e);
		goto done;
	case 4:
		p = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		if (p == 0) {
			goto minus_one;
		}
		*(int*) (e + 0xcc) = ch_StartMovement(*(int*) (e + 0xb8), *(int*) (e + 0xb0), -1, 0, 0, (char*) 0x6a7e18);
		*(int*) (e + 0x84) = cm_SendSetHE(5, e);
		goto done;
	case 5:
		p = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			goto minus_one;
		}
		if (*(char**) (*(char**) (p + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 4, 0);
			goto done;
		}
		n = gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime);
		switch (*(int*) (e + 0xbc)) {
		case 2:
			c = 0x21c;
			break;
		case 4:
			c = 0xb40;
			break;
		default:
			c = 0x5a0;
			break;
		}
		c -= n;
		n = c > 5 ? c : 5;
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), n / 60, n % 60, 0);
		cm_RequestKillSpieler(*(int*) (e + 0xb8), 1);
		*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
		goto done;
	case 6:
		n = gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime);
		if (n > 0x5a0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(4, e);
			goto done;
		}
		q = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		if (q == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			goto minus_one;
		}
		r = he_FindNearestAction0x18(h, q, *(int*) (e + 0xc4));
		if (r != 0) {
			*(int*) (e + 0xac) = *(int*) (r + 0xb4);
			*(int*) (e + 0xc4) = *(int*) (r + 4);
			*(int*) (e + 0xc8) = 1;
			cm_SendCancelCharacterActions(*(int*) (q + 4));
			ch_StartMovement(*(int*) (q + 4), *(int*) (e + 0xac), -1, 0, 1, (char*) 0x6a7e3c);
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
			*(int*) (e + 0x84) = cm_SendSetHE(7, e);
			goto done;
		}
		ai_FindEntityInFavorRange((unsigned short*) h, 0, (int) 0xa7f4c7a0, 1, 0.0f, 100.0f, (int*) (e + 0xac));
		*(int*) (e + 0xc4) = -1;
		*(int*) (e + 0xc8) = 0;
		cm_SendCancelCharacterActions(*(int*) (q + 4));
		ch_StartMovement(*(int*) (q + 4), *(int*) (e + 0xac), -1, 0, 1, (char*) 0x6a7e3c);
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 0xf, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(6, e);
		goto done;
	case 7:
		n = gm_GetElapsedMinutes(e + 0x44, (char*) &gm_GameTime);
		q = gm_LookupEntityRecordById(*(int*) (e + 0xb8));
		if (q == 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
			goto done;
		}
		if (n > 0x5a0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(4, e);
			goto done;
		}
		r = he_StartHandlungSearch(2, 0, 0x18, 1, *(int*) (e + 0xc4));
		if (he_RunSpyKillerCheck(q, e, r) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(6, e);
			goto done;
		}
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 6, 0);
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		*(int*) (e + 0x84) = cm_SendSetHE(7, e);
		goto done;
	}
done:
	return;
state_minus:
	if (*(unsigned char*) (e + 0x78) & 2) {
		if (gm_LookupEntityRecordById(*(int*) (e + 0xb8)) != 0) {
			cm_RequestKillSpieler(*(int*) (e + 0xb8), 1);
		}
		if (*(int*) (e + 0x70) == -1) {
			he_PostEntityMessage(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 8)].entity_id, -1, g_14b5304, 1, 0x5fa, (char*) 0x6a7e24);
		}
	}
	he_FreeAction(e);
}
