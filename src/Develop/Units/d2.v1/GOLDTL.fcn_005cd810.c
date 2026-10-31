extern int g_772514;
extern int g_67d370;
extern int g_774654;
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_14ce8d8;
extern int g_14ce8e0;
extern int g_14ce8e8;
extern float g_662cf8;
extern float g_664e88;
extern float g_6660d4;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_004e8b80(int, int, char*);
int __cdecl fcn_004e8cb0(int, int, char*);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005463a0(int, int, ...);
int __cdecl he_fn_Handlung(void);
int __cdecl cm_ChkCutsceneReady(int, unsigned short);
float __cdecl fcn_004fef80(char*);
int __cdecl fcn_005c9f10(int, int, int, int, int, short*);
int __cdecl fcn_005c99a0(int, int, int, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005cdd90(int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);

typedef struct {
	int ent;
	int h1;
	int h2;
	int text;
	int pad10;
	int pad14;
	int pad18;
	int text1;
	int text2;
	int text3;
	int text4;
	int pad2c;
	int pad30;
	int pad34;
} Rec_5cd810;

/* ADDRESS: GOLDTL 0x005cd810 */
void __cdecl fcn_005cd810(int a0)
{
	Rec_5cd810 rec[8];
	char src2[0x90];
	char src1[0x80];
	short* sel2;
	int sel;
	int dlg;
	char* ent;
	char* p;
	float f;
	int count;
	int again;
	int i;
	int j;

	count = 0;
	sel2 = 0;
	dlg = fcn_00470820(0, 0, "special\\amt2");
	fcn_00471b60(dlg);
	sel = 0;
	again = 1;
	for (;;) {
		if (again) {
			d2_SetForm(dlg, 2);
			io_AppendText(0x6811b0);
			if (sel)
				io_AppendText(0xa0, *sel2);
			else
				io_AppendText(0x6a9ac4, a0 + 0x12b2);
			d2_SetForm(dlg, 3);
			io_AppendText(0x6811b0);
			d2_SetForm(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			for (i = 0; i < 8; i++) {
				rec[i].ent = 0;
				rec[i].h1 = -1;
				rec[i].text = 0;
			}
			if (((1 <= a0) && (a0 <= 6)) || (a0 == 8)) {
				count = fcn_004e8b80(a0, 6, src1);
				if (count >= 1) {
					for (i = 0; i < count; i++) {
						rec[i].ent = gm_LookupEntityRecordById(*(int*) (src1 + i * 0x18 + 4));
						rec[i].text = *(unsigned char*) (src1 + i * 0x18 + 8);
					}
				}
			} else {
				if (a0 != 7)
					return;
				count = fcn_004e8cb0(0, 6, src2);
				if (count >= 1) {
					for (i = 0; i < count; i++) {
						rec[i].ent = gm_LookupEntityRecordById(*(int*) (src2 + i * 0x18 + 4));
						rec[i].text = *(unsigned char*) (src2 + i * 0x18 + 8);
					}
				}
			}
			if (!count)
				return;
			for (i = 0; i < count; i++) {
				ent = (char*) rec[i].ent;
				if (!ent)
					continue;
				rec[i].text2 = 0;
				rec[i].text1 = 0x6ca - (*(unsigned char*) (ent + 0xc) != 0);
				if ((*(unsigned char*) (g_774970 * 0x21c + 0x7f4ca9) != *(unsigned char*) (ent + 9)) && (*(unsigned int*) (ent + 0x1c8) & 0x800000)) {
					j = fcn_005463a0(1, 0, 0x6f);
					while (j) {
						if ((*(int*) (j + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
							rec[i].text2 = 0x6cc;
							break;
						}
						j = he_fn_Handlung();
					}
				}
				rec[i].text3 = 0;
				if (cm_ChkCutsceneReady(*(int*) (ent + 4), g_774970) >= 1) {
					rec[i].text3 = 0x6cd;
				} else {
					j = fcn_005463a0(1, 0, 0x18);
					while (j) {
						if ((*(unsigned short*) (j + 8) == g_774970) && (*(int*) (ent + 4) == *(int*) (j + 0xc4))) {
							rec[i].text3 = 0x6ce;
							break;
						}
						j = he_fn_Handlung();
					}
				}
				rec[i].text4 = 0;
				j = fcn_005463a0(1, 0, 0x45);
				while (j) {
					if ((*(int*) (j + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
						rec[i].text4 = 0x6cb;
						break;
					}
					j = he_fn_Handlung();
				}
				if (!rec[i].text4) {
					f = fcn_004fef80(ent);
					if (f >= g_662cf8) {
						if (f >= g_664e88) {
							if (f >= g_6660d4)
								rec[i].text4 = 0x6cf;
							else
								rec[i].text4 = 0x6d0;
						} else {
							rec[i].text4 = 0x6d1;
						}
					} else {
						rec[i].text4 = 0x6d2;
					}
				}
			}
			p = (char*) sel2;
			if (!p)
				p = (char*) (g_774970 * 0x21c + 0x7f4ca0);
			if (a0 && (a0 != 7))
				fcn_005c9f10(g_772514, a0, 0, count, (int) rec, (short*) p);
			else
				fcn_005c99a0(g_772514, a0, 0, count, (int) rec, (int) p);
			for (i = 0; i < count; i++) {
				fcn_00472640(rec[i].h1, 1);
				if (rec[i].h2 != -1)
					fcn_00472640(rec[i].h2, 1);
			}
			again = 0;
		}
		if (g_14ce8e0) {
			g_774654 = 1;
			goto loopend;
		}
		if (g_14ce8e8) {
			if (sel == 0) {
				sel2 = 0;
				i = 0;
				while (i < count) {
					if (rec[i].h2 == g_67d370)
						break;
					i++;
				}
				if ((0 <= i) && (i < count)) {
					ent = (char*) rec[i].ent;
					if (ent) {
						sel2 = 0;
						again = 1;
						if (*(unsigned short*) ent != 0xffff) {
							sel2 = (short*) ent;
							sel = 1;
						}
					}
				}
				goto loopend;
			}
		} else {
			if (sel == 0)
				goto select;
			sel = 0;
			sel2 = 0;
			again = 1;
			goto loopend;
		}
select:
		if (g_14ce8d8 && (g_100f1dc != -1)) {
			if (count > 0) {
				i = 0;
				while (i < count) {
					if (rec[i].h1 == g_67d370)
						break;
					i++;
				}
				if ((0 <= i) && (i < count)) {
					ent = (char*) rec[i].ent;
					if (!ent || (*(unsigned short*) ent == 0xffff)) {
						sel2 = 0;
						sel = 0;
					}
					fcn_00471af0(dlg, 0);
					fcn_005cdd90(rec[i].text, (int) ent);
					fcn_00471af0(dlg, 1);
				}
			}
			again = 1;
		}
loopend:
		if (!fcn_005373e0(0x5cd810, 0x657c7)) {
			fcn_00471e30(dlg);
			return;
		}
	}
}
