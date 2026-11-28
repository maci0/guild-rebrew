

typedef struct
{
	int dlg;
	int flags;
	int win;
	char pad0c[0x4c];
	int msg;
	char text[4];
} MsgBox;
// SIZE 0x60

extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern int g_774a64;
extern char s_6ab3e4[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
void __cdecl d2_AddWindowFrame(int, int);
void __cdecl d2_BringWindowToFront(int);
int __cdecl io_AppendText(char*, ...);

/* ADDRESS: GOLDDE 0x005957d0 */
int __cdecl d2_InitLandkarteDialog(MsgBox* m)
{
	m->dlg = d2_LoadForm(0, 0, s_6ab3e4);
	d2_CenterForm(m->dlg, 3);
	d2_SetForm(m->dlg, 0);
	m->win = d2_CreateChildWindow(0x4a, 0x4c, 0x206, 0x164, 0, d2_CurrentWindowId);
	d2_CurrentWindowId = m->win;
	*(int*) (d2_CurrentWindow + 0x3c8) = g_774a64;
	d2_SetForm(m->dlg, 0);
	if (m->msg == 0) {
		if (m->flags & 4) {
			d2_AddWindowFrame(d2_CurrentWindowId, 0x727);
		}
		else if (m->flags & 2) {
			d2_AddWindowFrame(d2_CurrentWindowId, 0x72b);
		}
		else if ((m->flags & 1) && m->text != 0) {
			d2_AddWindowFrame(d2_CurrentWindowId, 0x723);
		}
		else if ((m->flags & 8) && m->text != 0) {
			d2_AddWindowFrame(d2_CurrentWindowId, 0x723);
		}
		else {
			d2_AddWindowFrame(d2_CurrentWindowId, 0x71f);
		}
	}
	else {
		d2_AddWindowFrame(d2_CurrentWindowId, m->msg);
	}
	if (m->text != 0) {
		d2_SetForm(m->dlg, 1);
		d2_BringWindowToFront(d2_CurrentWindowId);
		io_AppendText(m->text);
	}
	if (m->flags & 0x10) {
		d2_SetForm(m->dlg, 2);
		d2_BringWindowToFront(d2_CurrentWindowId);
	}
	return m->dlg;
}
