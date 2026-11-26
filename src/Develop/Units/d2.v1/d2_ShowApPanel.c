extern int __cdecl fcn_00470820(int a, int b, char *name);
void __cdecl d2_CenterDialogWindows(int obj);
void __cdecl d2_SetForm(int obj, int a);
int __cdecl io_AppendText(int id, ...);
void __cdecl fcn_005c4d00(int win, int sub, int idx, int flag);
int __cdecl d2_GetControlValue(int key);
int __cdecl main_RunFrameLoop(void *proc, int msg);
void __cdecl d2_DestroyForm(int obj);

/* ADDRESS: GOLDTL 0x005c4dc0 */
void __cdecl d2_ShowApPanel(void)
{
	int dlg;
	int i;
	int v;
	int* p;
	int* q;

	dlg = fcn_00470820(0, 0, (char *) 0x6ac6b4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1ef9);
	fcn_005c4d00(dlg, 0, *(unsigned short *) 0x774970, 0);
	*(int *) 0x100f1dc = -1;
	do {
		if (*(int *) 0x14ce8e0 != 0) {
			*(int *) 0x774654 = 1;
		}
		if (*(int *) 0x100f1dc == 2) {
			v = *(int *) 0x67d370;
			p = (int *) 0x776ca4;
			q = (int *) 0x776ca0;
			for (i = 0; i < 0x100; i++) {
				if (p[i * 2] != 0 && q[i * 2] == v) {
					*(int *) (p[i * 2] + 8) = d2_GetControlValue(q[i * 2]);
					d2_SetForm(dlg, 0);
					io_AppendText(0x6811b0);
					fcn_005c4d00(dlg, 0, *(unsigned short *) 0x774970, 0);
					break;
				}
			}
		}
	} while (main_RunFrameLoop((void *) d2_ShowApPanel, 0x657c7) != 0);
	d2_DestroyForm(dlg);
}
