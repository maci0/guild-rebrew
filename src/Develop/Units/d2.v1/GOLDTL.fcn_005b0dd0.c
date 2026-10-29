

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

extern int g_772514;
extern char* g_77255c;
extern int g_774a64;
extern char s_6ab3e4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void __cdecl fcn_005b01c0(int, int);
void __cdecl fcn_0046f540(int);
int __cdecl fcn_00519190(char*, ...);

int __cdecl fcn_005b0dd0(MsgBox* m)
{
	m->dlg = fcn_00470820(0, 0, s_6ab3e4);
	fcn_00471d80(m->dlg, 3);
	d2_SetForm(m->dlg, 0);
	m->win = fcn_0046f100(0x4a, 0x4c, 0x206, 0x164, 0, g_772514);
	g_772514 = m->win;
	*(int*) (g_77255c + 0x3c8) = g_774a64;
	d2_SetForm(m->dlg, 0);
	if (m->msg == 0) {
		if (m->flags & 4) {
			fcn_005b01c0(g_772514, 0x727);
		}
		else if (m->flags & 2) {
			fcn_005b01c0(g_772514, 0x72b);
		}
		else if ((m->flags & 1) && m->text != 0) {
			fcn_005b01c0(g_772514, 0x723);
		}
		else if ((m->flags & 8) && m->text != 0) {
			fcn_005b01c0(g_772514, 0x723);
		}
		else {
			fcn_005b01c0(g_772514, 0x71f);
		}
	}
	else {
		fcn_005b01c0(g_772514, m->msg);
	}
	if (m->text != 0) {
		d2_SetForm(m->dlg, 1);
		fcn_0046f540(g_772514);
		fcn_00519190(m->text);
	}
	if (m->flags & 0x10) {
		d2_SetForm(m->dlg, 2);
		fcn_0046f540(g_772514);
	}
	return m->dlg;
}
