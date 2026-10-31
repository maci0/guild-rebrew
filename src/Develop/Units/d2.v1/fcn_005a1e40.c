extern int g_772514;
extern int g_772500;
extern int g_77255c;
extern int g_14ce8e0;
extern int g_774654;

void* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(void* dlg);
void __cdecl d2_SetForm(void* dlg, int panel);
int __cdecl fcn_005340f0(int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_0046f2c0(int a, int b);
int __cdecl io_AppendText();
void __cdecl fcn_005ca560(void* slot);
void __cdecl fcn_005ca740(int x, int y, int a, int b, void* slot, int c);
int __cdecl fcn_005373e0(void (*fn)(void), int code);
void __cdecl fcn_00471e30(void* dlg);

/* ADDRESS: GOLDTL 0x005a1e40 */
void __cdecl fcn_005a1e40(int a0, int* a1)
{
	int changed;
	void* dlg;
	int* src;
	int sel[4][14];
	int* p;
	int* q;
	int n;
	int ent;
	int i;

	memset(sel, 0, sizeof(sel));
	dlg = fcn_00470820(0, 0, "locations\\Wirtshaus\\Stammtisch");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetOverlayAnimation(0, 0);
	src = (int*) ((char*) a1 + 0x1c);
	for (;;) {
		changed = 0;
		n = 0;
		q = src;
		p = sel[0];
		for (i = 0; i < 4; i++) {
			ent = gm_LookupEntityRecordById(*q);
			if (ent != p[0]) {
				changed = 1;
			}
			if (ent != 0) {
				p[0] = ent;
				n++;
				p += 0xe;
			}
			q++;
		}
		for (i = n; i < 4; i++) {
			sel[i][0] = 0;
		}
		if (changed) {
			d2_SetForm(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			io_AppendText((char*) 0x188c, a0);
			if (n == 0) {
				io_AppendText((char*) 0x188e);
			} else {
				int x0 = *(int*) (g_77255c + 0xc) + *(short*) (g_772500 + 0x1ebd8) * -2;
				p = sel[0];
				for (i = 0; i < n; i++) {
					p[0xc] = 1;
					p[4] = (i & 1) * (x0 / 3) + -10 + (x0 % 3) / 2 + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i & 1);
					p[5] = (i / 2) * 0x82 + 100;
					fcn_005ca560(p);
					fcn_005ca740(p[4], p[5], g_772514, 0x54, p, 1);
					p += 0xe;
				}
			}
			d2_SetForm(dlg, 2);
			fcn_0046f2c0(g_772514, 1);
			if (n == 4) {
				io_AppendText((char*) 0x1892);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (fcn_005373e0((void (*)(void)) fcn_005a1e40, 0x677c7) == 0) {
			break;
		}
	}
	fcn_00471e30(dlg);
}
