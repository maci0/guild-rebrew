/* panel/slot record edited by this handler */
typedef struct {
	char p0[8];
	unsigned short id;
	char p10[0x42];
	char name[0x52];
	char p6c[4];
	int state;
	char* handle;
	char p7c[0x30];
	unsigned char kind;
	char paf[1];
	int sub;
	int base;
} Panel;

extern unsigned short g_774970;
extern char g_774964;
extern char g_7f4ca0[];
extern int g_100f884;
extern char g_7749e8;
extern int g_7749e4;
extern int g_100f1dc;

int __cdecl fcn_00500cb0(char* name, char* list);
void __cdecl fcn_00545780(Panel* p);
void __cdecl fcn_00546190(Panel* p);
void __cdecl fcn_00545670(Panel* p, int a1, int a2, char* fmt, int a4);
void __cdecl fcn_00471b60(int dlg);
void __cdecl d2_SetForm(int dlg, int a1);
void __cdecl fcn_00519190(int a0);
void __cdecl fcn_004c30a0(int a0, int a1, char* fmt, int a3, int a4);

/* ADDRESS: GOLDTL 0x00555a80 */
void __cdecl fcn_00555a80(Panel* p)
{
	char* rec;
	int id;
	int v;

	id = (int) p->id;
	rec = (char*) g_7f4ca0 + id * 540;
	if (p->id != g_774970) {
		return;
	}
	if (g_774964 == 0) {
		return;
	}
	if (fcn_00500cb0(p->name, (char*) 0x7f4c00) == 1) {
		return;
	}
	if (p->state == -2 || p->state == -1) {
		goto update;
	}
	if (*(unsigned short*) rec == 0xffff) {
		goto update;
	}
	if (p->state == 0) {
		goto open;
	}
	if (p->state != 1) {
		return;
	}
	if (p->handle == 0) {
		p->state = 0;
		return;
	}
	if ((g_100f884 != *(int*) (p->handle + 8) && g_7749e8 == 0) && g_100f1dc == -1) {
		return;
	}
	if (g_100f1dc == 2) {
		fcn_00545780(p);
		fcn_00546190(p);
		return;
	}
	if (g_7749e8 == 0) {
		return;
	}
	if (g_7749e4 != (int) p->handle) {
		return;
	}
	g_7749e8 = 0;
	fcn_00545780(p);
	fcn_00546190(p);
	return;
open:
	if (p->handle == 0) {
		fcn_00545670(p, 0, 0, (char*) 0x6a5ec4, 0x5ec);
	}
	if (p->handle == 0) {
		return;
	}
	fcn_00471b60(*(int*) (p->handle + 8));
	d2_SetForm(*(int*) (p->handle + 8), 1);
	fcn_00519190(0x16c8);
	v = p->base + (int) p->kind * 6 + 0x16c9;
	fcn_00519190(v);
	fcn_004c30a0(-7, 0, (char*) 0x6a5e40, 0, 0x64);
	fcn_004c30a0(-8, 0, (char*) 0x6a5eb4, p->base + (int) p->kind * 6, 0xfa);
	if (p->sub < 6) {
		fcn_00519190(p->sub + 0x16e6);
		fcn_004c30a0(-8, 0, (char*) 0x6a5ea4, p->sub - 1, 0x64);
	} else {
		fcn_00519190((int) p->kind + 0x16ec);
		fcn_004c30a0(-8, 0, (char*) 0x6a5e98, (int) p->kind, 0x64);
	}
	fcn_004c30a0(-7, 0, (char*) 0x67d908, 0, -1);
	d2_SetForm(*(int*) (p->handle + 8), 2);
	fcn_00519190(0x16f1);
	p->state = 1;
	return;
update:
	if (p->handle != 0) {
		fcn_00545780(p);
	}
	fcn_00546190(p);
}
