int __cdecl fcn_004f39b0(void);
int __cdecl fcn_004f5dd0(void);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_0050f980(unsigned short, unsigned short, int);
int __cdecl fcn_005c6270(char *, int);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(char *, int, int);
int __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4670(int, int, int, int *);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c5150(int, int, int, int);
int __cdecl fcn_004c4450(int);
char *__cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_0046f2c0(int, int);
void __cdecl fcn_005ca560(int *);
void __cdecl fcn_005caaa0(int, int, int, int *);
void __cdecl fcn_005c91c0(char *, int, int, int, int);
void __cdecl fcn_005b2150(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_0050e600(void);
void __cdecl fcn_0050e670(void *, void *);
int __cdecl fcn_00451840(void *, void *);
void __cdecl fcn_00438b40(int, void *);
void __cdecl fcn_00438cb0(int, void *);
void __cdecl fcn_0052d820(void);
int __cdecl fcn_005abd60(void);

/* Church indulgence ("Ablass") dialog: shows the indulgence panel for the
 * current town, then the detail columns once a choice was accepted. */
/* ADDRESS: GOLDTL 0x005ab3e0 */
void __cdecl fcn_005ab3e0(int a0)
{
	int count;
	int kind;
	int cost;
	int dlg;
	int item;
	int ent;
	int i;
	int col;
	int changed;
	int val;
	int sel;
	int row[0x20];
	int cur[5];
	int prev[5];
	int idx[5];
	int text[0x100];

	count = fcn_004f39b0();
	kind = fcn_004f5dd0();
	cost = 0;
	if (kind != 0) {
		cost = (int) ((float) gm_WalkEntityChain(*(unsigned short *) 0x774970) * 0.005f);
		if (*(unsigned short *) (a0 + 0x27) != *(unsigned short *) 0x774970) {
			fcn_0050f980(*(unsigned short *) 0x774970, *(unsigned short *) (a0 + 0x27), 1);
		}
		if (fcn_005c6270((char *) (*(unsigned short *) 0x774970 * 0x21c + 0x7f4ca0), 0x2c6) != 0) {
			cost = cost / 2;
		}
	}
	dlg = fcn_00470820(0, 0, (char *) 0x6ab014);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(*(int *) 0x772514);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1960, "Locations\\Kirche\\Ablass2");
	if (cost < 1) {
		io_AppendText(0x1961, *(unsigned short *) 0x774970);
		item = 0;
	} else {
		io_AppendText(0x1962, count, cost);
		d2_SetForm(dlg, 2);
		io_AppendText(0x1963, count, cost);
		item = fcn_00472250(dlg, 2, 0);
	}
	*(int *) 0x100f1dc = -1;
	changed = 0;
	do {
		if (*(int *) 0x14ce8e0 == 0) {
			if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == item &&
			    fcn_00526010((char *) (*(unsigned short *) 0x774970 * 0x21c + 0x7f4ca0), cost, *(unsigned char *) 0x773d75) != 0) {
				fcn_004c4510((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca0,
					     *(int *) ((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca4));
				fcn_004c4670(4, 1, 0x1ac, &cost);
				fcn_004c5360();
				if (*(unsigned short *) (a0 + 0x27) == 0xffff ||
				    *(unsigned short *) (a0 + 0x27) == *(unsigned short *) 0x774970) {
					sel = fcn_004c5150(-1, *(int *) ((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca4),
							   *(unsigned char *) 0x773d75, cost);
				} else {
					val = count;
					sel = fcn_004c5150(-1, *(int *) ((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca4),
							   *(unsigned char *) 0x773d75, val);
					sel = fcn_004c5150(*(int *) ((int) *(unsigned short *) (a0 + 0x27) * 0x21c + 0x7f4ca4), -1,
							   *(unsigned char *) 0x773d75, val);
					fcn_005b2150();
				}
				while (sel != -1 && fcn_004c4450(sel) == 0) {
					fcn_00535960();
				}
				ent = fcn_0050e600();
				io_FormatTextBuffer((char *) text, 0x1964, cost, ent, *(unsigned short *) 0x774970);
				fcn_00526120((char *) text, 0x100);
				changed = 1;
				*(int *) 0x774654 = 1;
			}
		} else {
			*(int *) 0x774654 = 1;
		}
	} while (fcn_005373e0((void *) 0x5ab3e0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	if (changed) {
		dlg = fcn_00470820(0, 0, (char *) 0x6ab048);
		fcn_00471b60(dlg);
		d2_SetForm(dlg, 0);
		fcn_005340f0(*(int *) 0x772514);
		d2_SetOverlayAnimation(0, 0);
		*(int *) 0x100f1dc = -1;
		do {
			fcn_0050e670(prev, cur);
			changed = 0;
			for (i = 0; i < 5; i++) {
				if (prev[i] != cur[i] || cur[i] != idx[i]) {
					changed = 1;
				}
				idx[i] = cur[i];
			}
			if (changed) {
				fcn_0046f2c0(*(int *) 0x772514, 1);
				io_AppendText(0x196b, *(int *) 0x772514);
				for (col = 0; col < 5; col++) {
					row[0] = 0;
					if (idx[col] != -1) {
						row[0] = idx[col] * 0x21c + 0x7f4ca0;
					}
					fcn_005ca560(row);
					fcn_005caaa0(row[1], row[2], *(int *) 0x772514, row);
					if (row[0] == 0) {
						strcpy((char *) text, *(char **) 0x14a6554);
					} else {
						io_FormatTextBuffer((char *) text, 0x196d, row[0]);
					}
					fcn_005c91c0((char *) text, row[1], row[2], 0x14, 0x53);
					io_FormatTextBuffer((char *) text, 0x196e, idx[col]);
					fcn_005c91c0((char *) text, row[1], row[2] + 0x19, 0x14, 0x53);
				}
			}
			if (*(int *) 0x14ce8e0 != 0) {
				*(int *) 0x774654 = 1;
			}
		} while (fcn_005373e0((void *) 0x5abd60, 0x677c7) != 0);
	}
	if (*(int *) 0x6b5cc0 != 0) {
		if (fcn_00451840((void *) 0x14ce880, (void *) 0x7e3a40) == 0) {
			*(int *) 0x6b5cc0 = 0;
		} else {
			*(int *) 0x6b5cc0 = 0;
			fcn_00438b40(*(int *) 0x6b8014, (void *) 0x7e3a40);
			fcn_00438cb0(*(int *) 0x6b8014, (void *) 0x7e3a50);
		}
	}
	fcn_0052d820();
	fcn_005abd60();
}
