extern char g_14a5320[];
extern char gm_EntitySlotTable[];
extern char io_RightButtonReleased[];
extern char d2_DialogCloseRequested[];
extern char d2_DialogButtonAction[];

int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int k);
int __cdecl d2_SetForm(int k, int i);
void __cdecl io_AppendText(int a);
int __cdecl main_RunFrameLoop(void* p, int a);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short id, int delta);
int __cdecl gm_CountChildren(char* e, int* out_count);
int __cdecl d2_ShowModalMessageBox(char* text, int flags);
int __cdecl d2_DestroyForm(int k);

/* ADDRESS: GOLDTL 0x005a06a0 */
/* ADDRESS: GOLDDE 0x00585520 */
void __cdecl d2_ShowWeinkellerDialog(void)
{
	char* slot;
	int h;
	int n;
	int mode;

	slot = (char*) &gm_EntitySlotTable + (unsigned int) *(unsigned short*) ((int) &d2_DialogCloseRequested + 0x31c) * 0x21c;
	h = d2_LoadForm(0, 0, "locations\\wohnsitz\\weinkeller");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x42cf);
	d2_SetForm(h, 2);
	io_AppendText(0x42d1);
	while (main_RunFrameLoop((void*) d2_ShowWeinkellerDialog, 0x677c7) != 0) {
		if (*(int*) &io_RightButtonReleased != 0) {
			*(int*) &d2_DialogCloseRequested = 1;
		}
		else if (*(char*) ((int) &io_RightButtonReleased + 0xe21) != 0) {
			*(int*) &d2_DialogCloseRequested = 1;
		}
		else if ((mode = *(int*) &d2_DialogButtonAction) == 2) {
			n = 0;
			if (gm_CountChildren(slot, &n) != 0) {
				gm_ApplyEntityHealthDelta(*(unsigned short*) slot, -2000);
			}
			else {
				d2_ShowModalMessageBox((char*) *(int*) ((int) &g_14a5320 + (n != 0 ? 0x42d3 : 0x42d2) * 4), 0);
				*(int*) &d2_DialogCloseRequested = 1;
			}
		}
		else if (mode == 1) {
			*(int*) &d2_DialogCloseRequested = 1;
		}
	}
	d2_DestroyForm(h);
}
