#include "Develop/DieGildeAddOn/game/client_data.h"
extern void __cdecl gm_ResolveEntityById(char**, int, int, int); extern char* __cdecl fcn_00502cd0(int, ...);
extern void __cdecl he_FreeAction(char*);
extern char* __cdecl he_StartHandlungSearch(int, int, int, ...);
extern int __cdecl ai_CheckFavorRankAcceptance(unsigned short*, unsigned short*);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl cm_BeginPacketFieldDelta(char*, unsigned int);
extern int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
extern void __cdecl cm_RequestChangeAttribute(void);
extern int __cdecl cm_SendSetHE(int, char*);
extern int __cdecl gm_CompareGameTime(char*, char*);
extern void __cdecl d2_CloseActionPopup(char*);
extern int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
extern int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
extern int __cdecl d2_SetForm(int, int);
extern void __cdecl io_AppendText(int, ...);
extern void __cdecl gm_AddTime(void*, int, int, int);
extern int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x0054bc90 */
void __cdecl he_RunInvitation(char* action)
{
	char text[512];
	char* v10;
	char* v13;
	char* v15;
	int v11;
	int v16;
	int idx;
	unsigned short v6;
	unsigned short* v3;
	unsigned short* v7;
	char v4;

	v10 = 0;
	v13 = 0;
	v15 = 0;
	if (*(int*) (action + 0x70) == -1 || *(int*) (action + 0x70) == -2) {
		if (*(int*) (action + 0x74))
			d2_CloseActionPopup(action);
		he_FreeAction(action);
		return;
	}
	if (*(int*) (action + 0xbc) == 0) {
		gm_ResolveEntityById(&v10, 0, 0, *(unsigned int*) (action + 0x10));
		if (v10 == 0) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
		v13 = fcn_00502cd0(*(unsigned int*) (v10 + 0x5d), 1, 0, 0x17);
		if (v13 == 0) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
		if (*(unsigned short*) (v10 + 0x27) == 0xffff) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
		v7 = (unsigned short*) ((unsigned int) *(unsigned short*) (v10 + 0x27) * 0x21c + (unsigned long) &g_7f4ca0);
		if (v7 == 0) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
	} else if (*(int*) (action + 0xbc) == 1) {
		v15 = he_StartHandlungSearch(2, 1, *(unsigned int*) (action + 0xc0), 0, 0x37);
		if (v15 == 0) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
		v7 = (unsigned short*) ((unsigned int) *(unsigned short*) (v15 + 8) * 0x21c + (unsigned long) &g_7f4ca0);
		if (v7 == 0) {
			if (*(int*) (action + 0x74))
				d2_CloseActionPopup(action);
			he_FreeAction(action);
			return;
		}
	} else {
		he_FreeAction(action);
		return;
	}
	v3 = (unsigned short*) ((unsigned int) *(unsigned short*) (action + 8) * 0x21c + (unsigned long) &g_7f4ca0);
	v4 = *(char*) ((unsigned int) *(unsigned short*) (action + 8) * 0x21c + (unsigned long) &g_7f4ca2);
	if (v4 != 6 && v4 != 7)
		*(int*) (action + 0x70) = 2;
	switch (*(int*) (action + 0x70)) {
	case 2:
		if (ai_CheckFavorRankAcceptance(v7, v3) == 1) {
			v16 = *(int*) (v3 + 2);
			if (*(int*) (action + 0xbc) == 0) {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v13 + 0x1c + idx * 4) == v16)
						break;
				}
			} else {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v15 + 0xac + idx * 4) == v16)
						break;
				}
			}
			if (idx >= 4) {
				he_FreeAction(action);
				return;
			}
			io_FormatTextBuffer(text, 0x1785, *v3);
		} else {
			v11 = -1;
			v16 = *(int*) (v3 + 2);
			if (*(int*) (action + 0xbc) == 0) {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v13 + 0x1c + idx * 4) == v16)
						break;
				}
				if (idx < 4) {
					cm_BeginPacketFieldDelta(v13, *(unsigned int*) (v13 + 2));
					cm_AppendPacketFieldDelta(4, 1, idx * 4 + 0x1c, (char*) &v11);
					cm_RequestChangeAttribute();
				}
			} else {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v15 + 0xac + idx * 4) == v16)
						break;
				}
				if (idx < 4) {
					*(int*) (v15 + 0xac + idx * 4) = -1;
					cm_SendSetHE(0, action);
				}
			}
			if (idx >= 4) {
				he_FreeAction(action);
				return;
			}
			io_FormatTextBuffer(text, 0x1786, *v3);
		}
		he_PostEntityMessage(*(int*) (v7 + 2), -1, text, 0, 0x5ec, 0);
		he_FreeAction(action);
		return;
	case 1:
		if (gm_CompareGameTime((char*) &gm_GameTime, action + 0x52) > 0) {
			d2_CloseActionPopup(action);
			*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
			return;
		}
		if (g_100f884 != *(int*) (*(int*) (action + 0x74) + 8))
			return;
		v11 = -1;
		if (*(int*) &g_100f1dc == -1)
			return;
		if (*(int*) &g_100f1dc == 2) {
			v16 = *(int*) (v3 + 2);
			if (*(int*) (action + 0xbc) == 0) {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v13 + 0x1c + idx * 4) == v16)
						break;
				}
			} else {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v15 + 0xac + idx * 4) == v16)
						break;
				}
			}
			if (idx < 4) {
				io_FormatTextBuffer(text, 0x1785, *v3);
				he_PostEntityMessage(*(int*) (v7 + 2), -1, text, 0, 0x5ec, 0);
			}
		} else if (*(int*) &g_100f1dc == 1) {
			v16 = *(int*) (v3 + 2);
			if (*(int*) (action + 0xbc) == 0) {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v13 + 0x1c + idx * 4) == v16)
						break;
				}
				if (idx < 4) {
					cm_BeginPacketFieldDelta(v13, *(unsigned int*) (v13 + 2));
					cm_AppendPacketFieldDelta(4, 1, idx * 4 + 0x1c, (char*) &v11);
					cm_RequestChangeAttribute();
				}
			} else {
				for (idx = 0; idx < 4; idx++) {
					if (*(int*) (v15 + 0xac + idx * 4) == v16)
						break;
				}
				if (idx < 4) {
					*(int*) (v15 + 0xac + idx * 4) = -1;
					cm_SendSetHE(0, action);
				}
			}
			if (idx < 4) {
				io_FormatTextBuffer(text, 0x1786, *v3);
				he_PostEntityMessage(*(int*) (v7 + 2), -1, text, 0, 0x5ec, 0);
			}
		}
		d2_CloseActionPopup(action);
		he_FreeAction(action);
		return;
	case 0:
		d2_CreateActionPopupSlot(action, 0, 0, (char*) 0x6a5a10, 0x5ec);
		if (*(int*) (action + 0x74) == 0) {
			he_FreeAction(action);
			return;
		}
		d2_SetForm(*(int*) (*(int*) (action + 0x74) + 8), 0);
		v6 = *v7;
		if (*(int*) (action + 0xbc) == 0)
			io_AppendText(0x1770, *(unsigned short*) (v10 + 0x27), *v3, action + 0xac, v10, v6, *v3);
		else
			io_AppendText(0x1771, *(unsigned short*) (v10 + 0x27), *v3, action + 0xac, v6, *v3);
		*(pos14_7f4c00*) (action + 0x44) = gm_GameTime;
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime(action + 0x52, 0x18, 0, 0);
		d3snd_PlaySoundEffect(-7, 0, (char*) 0x6a5a34, 0);
		*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
		return;
	}
}
