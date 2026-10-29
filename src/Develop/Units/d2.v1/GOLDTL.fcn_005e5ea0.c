extern int g_772514;
extern int g_77255c;
extern int g_6b7fac;
extern int g_14b5af8;
extern int g_14b5afc;
extern char g_7f4c00[];

int __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00510550(char*);
int __cdecl fcn_00510550b(char*, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);


/* "Locations\zigeuner\blutrache" blood-revenge dialog. Partial body: entry
 * UI snapshot, dialog and timer construction, choice-list setup and the
 * modal frame loop; the per-frame update block and post-loop aftermath are
 * still missing. */
/* ADDRESS: GOLDTL 0x005e5ea0 */
void __cdecl fcn_005e5ea0(char* participant)
{
	int ui[4];
	int dlg;
	int timer1;
	int timer2;
	int list;
	int n;

	ui[0] = *(int*) ((char*) g_7f4c00);
	ui[1] = *(int*) ((char*) g_7f4c00 + 4);
	ui[2] = *(int*) ((char*) g_7f4c00 + 8);
	*(short*) (&ui[3]) = *(short*) ((char*) g_7f4c00 + 0xc);
	fcn_00500bb0((char*) ui, 0x18, 0, 0);
	*(short*) ((char*) ui + 4) = (short) fcn_0042e410(2);
	*(short*) ((char*) ui + 4) = (short) (*(short*) ((char*) ui + 4) + 0x15);
	*(short*) ((char*) ui + 6) = 0;
	*(short*) ((char*) ui + 8) = 0;
	dlg = fcn_00470820(0, 0, "Locations\\zigeuner\\blutrache");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 2);
	timer1 = fcn_004677e0((*(int*) ((char*) g_77255c + 0xc) - 300) / 2, 10, 300, 0, 100, 0x75, 0x42, g_772514);
	fcn_00472380(timer1, 0, 100, 0);
	d2_SetForm(dlg, 2);
	timer2 = fcn_004677e0(0x57, 7, 200, 0, 100, 0x7b, 2, g_772514);
	list = fcn_00510550(participant);
	n = fcn_00510550b(participant, 0, 1);
	(void) list;
	fcn_00472380(timer2, 0, n - 1, 0);
	d2_SetForm(dlg, 3);
	fcn_00533a60(g_772514, 0, ui, 2, g_14b5af8, g_14b5afc);
	while (fcn_005373e0((int) fcn_005e5ea0, 0x677c7) != 0) {
		/* per-frame update: 0x5719d0 choice query, 0x500d20/0x500bb0
		 * snapshot refresh, 0x519190 text updates, 0x525f60 payout */
	}
	fcn_00471e30(dlg);
}
