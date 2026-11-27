

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
extern char* g_77255c;
extern int g_774a64;
extern char s_6ab3e4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
void __cdecl d2_AddWindowFrame(int, int);
void __cdecl d2_BringWindowToFront(int);
int __cdecl io_AppendText(char*, ...);

int __cdecl fcn_005b0dd0(MsgBox* m)
{
	m->dlg = fcn_00470820(0, 0, s_6ab3e4);
	fcn_00471d80(m->dlg, 3);
	d2_SetForm(m->dlg, 0);
	m->win = d2_CreateChildWindow(0x4a, 0x4c, 0x206, 0x164, 0, d2_CurrentWindowId);
	d2_CurrentWindowId = m->win;
	*(int*) (g_77255c + 0x3c8) = g_774a64;
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
