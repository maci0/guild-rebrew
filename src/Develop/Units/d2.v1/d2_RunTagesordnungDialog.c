extern char g_85a0a0[];
extern char io_RightButtonReleased[];
extern char d2_DialogCloseRequested[];
extern int d2_CurrentWindowId;
extern char gm_EntitySlotTable[];

int __cdecl amt_FindOfficeSlotsByKind(int, int, char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl amt_GetSpecialOfficeId(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_OpenTagesordnungDialog(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005ce110 */
/* ADDRESS: GOLDDE 0x005afba0 */
void __cdecl d2_RunTagesordnungDialog(int a0, int a1, int level)
{
	char rec[0x90];
	char* s;
	char* v5;
	char* otherEntity;
	unsigned short* h;
	unsigned short* pick[4];
	int dialog;
	int v9;
	int n;
	int i;
	int any;
	int j;
	int k;
	int found;
	int w;

	n = amt_FindOfficeSlotsByKind(a0, 6, rec);
	if (n <= 0) {
		return;
	}
	dialog = d2_LoadForm(0, 0, "special\\tagesordnung");
	d2_CenterDialogWindows(dialog);
	d2_SetForm(dialog, 2);
	w = d2_CurrentWindowId;
	d2_SetForm(dialog, 4);
	d2_AddWindowScrollButtons(0xffffffff, 0xffffffff, d2_CurrentWindowId, w, 0x767);
	d2_SetForm(dialog, 3);
	w = d2_CurrentWindowId;
	d2_SetForm(dialog, 5);
	d2_AddWindowScrollButtons(0xffffffff, 0xffffffff, d2_CurrentWindowId, w, 0x767);
	d2_SetForm(dialog, 1);
	io_AppendText(a0 + 0x13a3);
	d2_SetForm(dialog, 2);
	io_AppendText(0x139e);
	found = 0;
	for (i = 0; i < n; i++) {
		if (rec[i * 0x18 + 0x10] == 2) {
			s = (char*) gm_LookupEntityRecordById(*(int*) (rec + i * 0x18 + 4));
			otherEntity = (char*) gm_LookupEntityRecordById(*(int*) (rec + i * 0x18 + 0x14));
			if (s != 0 && otherEntity != 0) {
				found |= 1;
				if (*(char*) (s + 9) == 0) {
					v9 = *(unsigned char*) (rec + i * 0x18 + 8) + 0x253;
				} else {
					v9 = *(unsigned char*) (rec + i * 0x18 + 8) + 0x27b;
				}
				io_AppendText(0x139f, *(unsigned short*) otherEntity, *(unsigned short*) s, v9);
			}
		}
	}
	if (found == 0) {
		io_AppendText(0x139d);
	}
	d2_SetForm(dialog, 3);
	if (a0 < 8) {
		io_AppendText(0x13a0);
		any = 0;
		for (j = 0; j < n; j++) {
			if (rec[j * 0x18 + 0x10] == 3) {
				found = 0;
				any |= 1;
				io_AppendText(0x13a1, *(unsigned char*) (rec + j * 0x18 + 8) + 0x253);
				k = 0;
				h = (unsigned short*) gm_EntitySlotTable;
				do {
					if (k >= 4) {
						break;
					}
					if (*(unsigned char*) ((char*) h + 0x168) == *(unsigned char*) (rec + j * 0x18 + 8)) {
						found |= 1;
						io_AppendText((int) "$A$Z%1N2", *h);
						k += 1;
					}
					h = (unsigned short*) ((char*) h + 0x21c);
				} while ((int) h < (int) &g_85a0a0);
				if (found == 0) {
					io_AppendText(0x139d);
				}
			}
		}
	} else {
		k = amt_GetSpecialOfficeId();
		v9 = 0;
		pick[0] = 0;
		pick[1] = 0;
		pick[2] = 0;
		pick[3] = 0;
		if (k != 0) {
			if (k == 0x24) {
				v9 = 0x8000;
			} else if (k != 0x25) {
				v9 = 0x4000;
			} else {
				v9 = 0x10000;
			}
		}
		i = 0;
		h = (unsigned short*) gm_EntitySlotTable;
		do {
			if ((int) h >= (int) &g_85a0a0) {
				break;
			}
			if ((*(unsigned int*) ((char*) h + 0x1cc) & v9) != 0) {
				pick[i] = h;
				i += 1;
			}
			h = (unsigned short*) ((char*) h + 0x21c);
		} while (i < 4);
		any = i;
		io_AppendText(0x13a2);
		if (k != 0) {
			io_AppendText(0x13a3, k + 0x253);
			for (j = 0; j < i; j++) {
				if (j == 0) {
					io_AppendText((int) "$2A$Z%1N2", *pick[0]);
				} else {
					io_AppendText((int) "$A$Z%1N2", *pick[j]);
				}
			}
		}
	}
	if (any == 0) {
		io_AppendText(0x139d);
	}
	do {
		if (*(int*) &io_RightButtonReleased != 0) {
			*(int*) &d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_OpenTagesordnungDialog, 0x657c7) != 0);
	d2_DestroyForm(dialog);
}
