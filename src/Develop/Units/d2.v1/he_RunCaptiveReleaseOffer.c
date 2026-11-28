extern char g_7f4c00[];
extern char g_6a5a10[];
extern char d2_DialogButtonAction[];
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CompareGameTime(void*, int);
void __cdecl d2_CreateActionPopupSlot(int, int, int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, int, int, int, int);
void __cdecl d2_CloseActionPopup(int);
void __cdecl he_FreeAction(int);
void __cdecl io_FormatTextBuffer(char*, int, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl cm_SendBlockCharacter(int, int, int);
int __cdecl gm_RollFavorRatioCheck(int, int, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);

/* ADDRESS: GOLDTL 0x00566d00 */
/* ADDRESS: GOLDDE 0x0054cd40 */
void __cdecl he_RunCaptiveReleaseOffer(int action)
{
	char buf[256];
	unsigned short* a;
	unsigned short* b;
	int entityId;


	int state;
	int selection;

	a = (unsigned short*) gm_LookupEntityRecordById(*(int*) (action + 0xac));
	b = (unsigned short*) gm_LookupEntityRecordById(*(int*) (action + 0xb0));
	if (!a || !b) {
		he_FreeAction(action);
		return;
	}
	if (*(char*) ((char*) b + 2) != 6 && *(char*) ((char*) b + 2) != 7) {
		if (gm_CompareGameTime((char*) action + 0x52, (int) &g_7f4c00) > 0) {
			return;
		}
		*(int*) (action + 0x70) = 2;
	}
	state = *(int*) (action + 0x70);
	switch (state) {
	case 0:
		d2_CreateActionPopupSlot(action, 0, 0, (int) &g_6a5a10, 0x5ec);
		d2_SetForm(*(int*) (*(int*) (action + 0x74) + 8), 0);
		entityId = *a;
		io_AppendText(0x19b2, entityId, *(int*) (action + 0xb4), entityId, entityId);
		*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
		return;
	case 1:
		if (*(int*) ((int) &d2_DialogButtonAction + 0x6a8) != *(int*) (*(int*) (action + 0x74) + 8)) {
			return;
		}
		selection = *(int*) &d2_DialogButtonAction;
		if (selection == -1) {
			return;
		}
		if (selection == 2) {
			io_FormatTextBuffer(buf, 0x19b3, *b);
			he_PostEntityMessage(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
			cm_SendBlockCharacter(*(int*) (a + 2), -(unsigned int) *(unsigned char*) ((char*) a + 0x1b1), 0);
		} else if (selection == 1) {
			io_FormatTextBuffer(buf, 0x19b4, *b, *(int*) (action + 0xb4));
			he_PostEntityMessage(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
		}
		d2_CloseActionPopup(action);
		he_FreeAction(action);
		return;
	case -1:
	case -2:
		d2_CloseActionPopup(action);
		he_FreeAction(action);
		return;
	case 2:



		if (gm_RollFavorRatioCheck(*a, *b, *(int*) (action + 0xb4), *(unsigned char*) ((char*) a + 0x1b1) * 16000)) {
			io_FormatTextBuffer(buf, 0x19b3, *b);
			he_PostEntityMessage(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
			cm_SendBlockCharacter(*(int*) (a + 2), -(unsigned int) *(unsigned char*) ((char*) a + 0x1b1), 0);
		} else {
			io_FormatTextBuffer(buf, 0x19b4, *b, *(int*) (action + 0xb4));
			he_PostEntityMessage(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
			cm_RequestCopyEntityData(*(int*) (a + 2), *(int*) (b + 2), 10, 1);
		}
		he_FreeAction(action);
		return;
	}
	return;
}
