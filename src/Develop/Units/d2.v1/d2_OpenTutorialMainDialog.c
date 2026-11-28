


extern int* d2_TutorialState;
extern char g_6a8354[];
extern char g_6a2f5c[];
extern int d2_CurrentWindowId;

void __cdecl d2_CreateActionPopupSlot(int, int, int, char*, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(char*, ...);
int __cdecl d2_GetWindowListItem(int, int, int);

int __cdecl d2_OpenTutorialMainDialog(void)
{
	int o;
	int v;

	o = d2_TutorialState[7];
	if (o == 0) {
		return -4;
	}
	if (*(int*) (o + 0x74) != 0) {
		return -4;
	}
	d2_CreateActionPopupSlot(o, 0, 0, g_6a8354, 0x5ec);
	v = *(int*) (d2_TutorialState[7] + 0x74);
	if (v == 0) {
		return -1;
	}
	d2_CenterForm(*(int*) (v + 8), 3);
	d2_CenterDialogWindows(*(int*) (*(int*) (d2_TutorialState[7] + 0x74) + 8));
	d2_SetForm(*(int*) (*(int*) (d2_TutorialState[7] + 0x74) + 8), 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(*(int*) (*(int*) (d2_TutorialState[7] + 0x74) + 8), 3);
	d2_TutorialState[8] = d2_GetWindowListItem(*(int*) (*(int*) (d2_TutorialState[7] + 0x74) + 8), 3, io_AppendText(g_6a2f5c, 0x7d));
	return 0;
}
