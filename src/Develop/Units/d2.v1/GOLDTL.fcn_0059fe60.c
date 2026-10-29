void __cdecl fcn_005338a0(void);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005463a0(int);
int __cdecl he_fn_Handlung(int);
int __cdecl fcn_00508e40(int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_0051af00(char *, int, ...);
unsigned short *__cdecl fcn_005cd440(void *, void *, void *, int);
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_004c5530(void *);
void __cdecl fcn_00471af0(int, int, int, int, int);
void __cdecl fcn_0059fa80(int, int, int);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00532ef0(void);

/* Residence ("Wohnsitz") dialog: builds the lover/wohnsitz panel, lists the
 * owner's buildings, and runs its message loop. */
/* ADDRESS: GOLDTL 0x0059fe60 */
void __cdecl fcn_0059fe60(int a0)
{
	int ids[4];
	int avail[4];
	int cost[4];
	int buttons[4];
	int box[0x14];
	int rec[8];
	char text_a[0x100];
	char text_b[0x100];
	char text_c[0x100];
	int dlg;
	int item;
	int btn;
	int ent;
	int n;
	int i;

	fcn_005338a0();
	dlg = fcn_00470820(0, 0, (char *) 0x6aa7dc);
	d2_SetForm(dlg, 0);
	fcn_005340f0(*(int *) 0x772514);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	d2_SetForm(dlg, 2);
	if (*(char *) ((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca9) == 0) {
		item = fcn_00519190(0x1a50);
	} else {
		item = fcn_00519190(0x1a51);
	}
	item = fcn_00472250(dlg, 2, item);
	*(int *) 0x100f1dc = -1;
	do {
		for (i = 0; i < 4; i++) {
			ids[i] = -1;
			avail[i] = -1;
			cost[i] = -1;
			buttons[i] = -1;
		}
		n = 0;
		ent = fcn_005463a0(1);
		while (ent != 0 && n < 4) {
			if (*(int *) (ent + 0xac) ==
			    *(int *) ((int) *(unsigned short *) 0x774970 * 0x21c + 0x7f4ca4)) {
				ids[n] = *(int *) (ent + 4);
				if (*(int *) (ent + 0x70) == 0) {
					avail[n] = 1;
				} else {
					avail[n] = 0;
				}
				cost[n] = *(int *) (ent + 0xb0);
				n++;
			}
			ent = he_fn_Handlung(item);
		}
		d2_SetForm(dlg, 1);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x6aa7d0, 0x1a4e, "$Z$[%s$]$N", "locations\\wohnsitz\\geliebte");
		fcn_00519190(0x1a4f, n);
		for (i = 0; i < 4; i++) {
			ent = fcn_00508e40(ids[i]);
			if (ent == 0) {
				break;
			}
			btn = fcn_00519190(0x1a52, *(unsigned short *) ent);
			btn = fcn_00472250(dlg, 1, btn);
			buttons[i] = btn;
			fcn_00472640(btn, avail[i]);
		}
		fcn_00472640(item, n < 4);
		if (*(int *) 0x14ce8e0 == 0) {
			if (*(int *) 0x100f1dc != -1) {
				if (*(int *) 0x67d370 == item) {
					int type_idx;
					int ent2;
					unsigned short *sel;

					type_idx = *(unsigned short *) 0x774970;
					box[0] = 0;
					fcn_0051af00(text_a, 0x1a53, 0x2040a -
						(*(char *) (type_idx * 0x21c + 0x7f4ca9) != 0));
					fcn_0051af00(text_b, 0x1a54, 0x2040a);
					sel = fcn_005cd440(box, text_a, text_b, 0);
					if (sel != 0) {
						if (*(char *) (type_idx * 0x21c + 0x7f4ca9) == 0) {
							fcn_0051af00(text_c, 0x1a55, *sel);
						} else {
							fcn_0051af00(text_c, 0x1a56, *sel);
						}
						if (fcn_00526120(text_c, 1) != 0) {
							rec[0] = 0x6f;
							rec[1] = 0;
							rec[2] = 2;
							rec[3] = *(int *) (type_idx * 0x21c + 0x7f4ca4);
							rec[4] = *(int *) (a0 + 1);
							fcn_004c5530(rec);
						}
					}
				} else {
					for (i = 0; i < 4; i++) {
						if (*(int *) 0x67d370 == buttons[i]) {
							ent = fcn_00508e40(ids[i]);
							fcn_00471af0(dlg, 0, 1, 1, ids[i]);
							fcn_0059fa80(*(unsigned short *) 0x774970 * 0x21c + 0x7f4ca0, ent,
								     fcn_005463a0(1));
							fcn_00471af0(dlg, 1, 0, 0, 0);
							break;
						}
					}
				}
			}
		} else {
			*(int *) 0x774654 = 1;
		}
	} while (fcn_005373e0((void *) 0x59fe60, 0x67fff) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
