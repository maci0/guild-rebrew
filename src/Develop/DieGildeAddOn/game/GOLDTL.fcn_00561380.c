extern unsigned char g_773d75;
extern int g_6b8010;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern float g_6628a0;
extern float g_664154;
extern float g_662cf8;
extern float g_665ec0;
extern float g_662c98;
extern int lpGebaeudePROT;
extern char g_68149c[];
extern char g_6a6560[];
extern char g_6a654c[];
extern char g_6a6538[];
extern char g_68bef4[];
extern char g_677640[];
extern unsigned char g_7f4ca0[];

int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void *__cdecl gm_GetEntityTableEntry(void *);
void __cdecl fcn_00529160(int, int, int, void *);
void __cdecl fcn_004c51a0(int, int, int, int);
void *__cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004c5da0(int, int, int, int, int, char *);
void *__cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00500bb0(void *, int, int, int);
int __cdecl fcn_0055be70(void *);
void __cdecl fcn_004c5ed0(int, char *, int);
int __cdecl fcn_004f4f60(int, int, int, int, int);
int __cdecl fcn_00500cb0(void *, int *);
float __cdecl fcn_00507e70(void *, void *, int);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_005c6270(void *, int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char *, int, int, int, int, int, char *);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_00545d40(int, int, char *, int, int, char *);
void *__cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_004c58b0(int, int);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_00546190(void *);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00422460(int, char *);
void __cdecl fcn_004193f0(int, int, int, int);
void *__cdecl fcn_00445600(void *, int, int, char *);
void __cdecl fcn_00455350(char *, char *, float *);
void __cdecl fcn_004c5530(void *);
void __cdecl fcn_00418000(int, float *, int, float, float, float, float, float, float, float *, int, int, int);
void __cdecl fcn_004185a0(int, float *, int, float, float, float, float, float, float, float, float, int);
void __cdecl fcn_00417d00(int, float *, int, float, float, float, float, int);
int __cdecl gm_RandomMod(unsigned short);

/* ADDRESS: GOLDTL 0x00561380 */
void __cdecl fcn_00561380(void *a0)
{
	unsigned char *p;
	unsigned char *r;
	unsigned char *e;
	unsigned char *recA;
	unsigned char *recB;
	unsigned char *v22;
	unsigned char *model;
	unsigned char *query;
	unsigned char *hand;
	char text[0x3f0];
	unsigned char msg[0xf8];
	float pos[8];
	unsigned char color[4];
	float v24;
	int v10;
	int n;

	p = (unsigned char *)a0;
	if (*(int *)(p + 0xc8) != -1 && !fcn_004c4450(*(int *)(p + 0xc8)))
		return;
	switch (*(int *)(p + 0x70)) {
	case 0:
		if (*(int *)(p + 0xc8) != -1 && !fcn_004c4450(*(int *)(p + 0xc8)))
			return;
		r = (unsigned char *)fcn_004c4480(*(int *)(p + 0xc8));
		if (r != 0) {
			e = (unsigned char *)gm_GetEntityTableEntry((unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0));
			if (e != 0)
				*(int *)(e + 0x28) = *(int *)(e + 0x28) + *(int *)(p + 0xd0);
			*(int *)(p + 0xc4) = *(int *)(r + 4);
			fcn_00529160(0, 0, *(unsigned short *)r, p);
			fcn_004c51a0(-1, *(int *)((unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0) + 4), g_773d75, *(int *)(p + 0xd0));
			*(int *)(p + 0xc8) = -1;
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			return;
		}
		goto label_56148f;
	case 1:
		r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
		if (r == 0) {
			*(int *)(p + 0x70) = -1;
			return;
		}
		*(int *)(p + 0xc8) = fcn_004c5da0(*(int *)(p + 0xc4), *(int *)(r + 1), -1, 0, 1, g_6a6560);
		*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
		return;
	case 2:
		*(int *)(p + 0xc8) = -1;
		r = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xc4));
		if (r == 0) {
			*(int *)(p + 0x70) = -1;
			return;
		}
		if (*(int *)(*(int *)(r + 0x184) + 0x128) != 0) {
			*(int *)(p + 0x52) = g_7f4c00;
			*(int *)(p + 0x56) = g_7f4c04;
			*(int *)(p + 0x5a) = g_7f4c08;
			*(unsigned short *)(p + 0x5e) = g_7f4c0c;
			fcn_00500bb0((void *)(p + 0x52), 0, 4, 0);
			*(int *)(p + 0x70) = 2;
			return;
		}
		*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
		return;
	case 3:
		r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
		if (r == 0 || *(unsigned short *)(r + 0x27) == 0xffff)
			goto label_56148f;
		*(void **)pos = r;
		pos[1] = 4000.0f;
		*(void **)(pos + 2) = p;
		pos[3] = 0.0f;
		if (fcn_0055be70(pos) == 0) {
			fcn_004c5ed0(*(int *)(p + 0xc4), g_68bef4, 1);
			fcn_004c5da0(*(int *)(p + 0xc4), *(int *)(p + 0x10), -1, 0, 1, g_6a6560);
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			return;
		}
		*(int *)(p + 0xc8) = fcn_004f4f60(0x18, 1,
			*(int *)((unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0) + 4),
			*(int *)((unsigned char *)(*(unsigned short *)(r + 0x27) * 0x21c + 0x7f4ca0) + 4),
			*(int *)(p + 0xac));
		*(int *)(p + 0x70) = 7;
		*(int *)(p + 0xcc) = *(int *)(pos + 1);
		*(int *)(p + 0x52) = g_7f4c00;
		*(int *)(p + 0x56) = g_7f4c04;
		*(int *)(p + 0x5a) = g_7f4c08;
		*(unsigned short *)(p + 0x5e) = g_7f4c0c;
		return;
	case 4:
		if (fcn_00500cb0((void *)(p + 0x52), &g_7f4c00) >= 0)
			return;
		*(unsigned char *)(p + 0xc2) = 0;
		r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
		if (r == 0 || *(unsigned short *)(r + 0x27) == 0xffff)
			goto label_56148f;
		recA = (unsigned char *)(*(unsigned short *)(r + 0x27) * 0x21c + 0x7f4ca0);
		recB = (unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0);
		if (gm_RandomFloat01() + fcn_00507e70(recB, recA, 2) < g_6628a0)
			goto label_561a7a;
		if (fcn_005c6270(recB, 0x2c0) != 0)
			goto label_561a7a;
		{
			io_FormatTextBuffer(text, 0x1735, *(unsigned short *)recA, r);
			he_MessageBoxQuickjump(*(int *)(recB + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
			if (*(unsigned short *)(r + 0x27) != 0xffff) {
				if (*(unsigned char *)(recA + 2) != 6 && *(unsigned char *)(recA + 2) != 7)
					fcn_004c54c0(*(int *)(recB + 4), *(int *)(recA + 4), -0x19, 1);
				else {
					io_FormatTextBuffer(text, 0x1736, r);
					he_MessageBoxQuickjump(*(int *)(recA + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, g_6a654c);
				}
				fcn_004f4f60(0x18, 1, *(int *)(recB + 4), *(int *)(recA + 4), *(int *)(r + 1));
			}
			v22 = (unsigned char *)0x7f4ca4;
			do {
				if ((*(unsigned char *)(v22 - 2) == 6 || *(unsigned char *)(v22 - 2) == 7)
					&& *(int *)v22 != *(int *)(recA + 4)
					&& *(int *)v22 != *(int *)(recB + 4)) {
					io_FormatTextBuffer(text, 0x1737, *(unsigned short *)recA, r);
					he_MessageBoxQuickjump(*(int *)v22, -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
				}
				v22 = v22 + 0x87 * 4;
			} while ((int)v22 < 0x85a0a4);
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			*(int *)(p + 0x52) = g_7f4c00;
			*(int *)(p + 0x56) = g_7f4c04;
			*(int *)(p + 0x5a) = g_7f4c08;
			*(unsigned short *)(p + 0x5e) = g_7f4c0c;
			fcn_00500bb0((void *)(p + 0x52), 0, 10, 0);
			return;
		}
		goto label_561aa2;
label_561a7a:
		recA = (unsigned char *)(*(unsigned short *)(r + 0x27) * 0x21c + 0x7f4ca0);
		recB = (unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0);
label_561aa2:
		if (fcn_005c6270(recA, 0x2c0)) {
			fcn_005100f0(*(int *)(recB + 4), -1);
			if (*(unsigned char *)(recB + 2) == 6 || *(unsigned char *)(recB + 2) == 7) {
				io_FormatTextBuffer(text, 0x1013, *(unsigned short *)recA, r);
				fcn_00545d40(*(int *)(recB + 4), -1, text, 0, 0x5fa, 0);
			}
			if (*(unsigned char *)(recA + 2) == 6 || *(unsigned char *)(recA + 2) == 7) {
				io_FormatTextBuffer(text, 0x1011, r);
				fcn_00545d40(*(int *)(recA + 4), -1, text, 0, 0x5fb, g_6a6538);
			}
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			return;
		}
		io_FormatTextBuffer(text, 0x1738, *(unsigned short *)(r + 0x27), r);
		he_MessageBoxQuickjump(*(int *)(recB + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
		if (*(unsigned short *)(r + 0x27) != 0xffff) {
			io_FormatTextBuffer(text, 0x1739, r);
			he_MessageBoxQuickjump(*(int *)(recA + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
			fcn_004f4f60(0x18, 1, *(int *)(recB + 4), *(int *)(recA + 4), *(int *)(r + 1));
			*(int *)(p + 0x70) = -1;
			return;
		}
		goto label_561d51;
	case 5:
		if (*(unsigned char *)(p + 0xc2) >= 1)
			goto label_56211d;
		{
			char names[3][64] = {"dummy_TUER", "dummy_FAHNE", "dummy_RAUCH_0"};
		v10 = g_6b8010;
		r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
		if (r == 0)
			goto label_561d51;
		if (*(unsigned char *)(p + 0xc2) == 0 && g_6b8010 == 0) {
			n = fcn_00422460(0, g_677640);
			if (n != 0)
				fcn_004193f0(n, *(int *)(r + 0x61), 0x6b, 0x463ea000);
			v24 = 3.0f;
		}
		fcn_004432d0(0, 1);
		model = (unsigned char *)*(int *)(r + 0x61);
		if (model != 0) {
			if (*(unsigned char *)(p + 0xc2) != 0) {
				n = gm_RandomMod(3) & 0xffff;
				model = (unsigned char *)fcn_00445600((void *)*(int *)(r + 0x61), 0x100, 0, &names[n][0]);
				if (model != 0)
					fcn_00455350((char *)model, (char *)model + 0x4c, pos);
				else
					model = (unsigned char *)fcn_00445600((void *)*(int *)(r + 0x61), 0x100, 0, g_68149c);
			} else {
				*(unsigned char *)(msg + 4) = 0x4f;
				*(int *)(msg + 8) = *(int *)((unsigned char *)(*(unsigned short *)(p + 8) * 0x21c + 0x7f4ca0) + 4);
				*(int *)(msg + 0xc) = -1;
				*(int *)(msg + 0x28) = g_7f4c00;
				*(int *)(msg + 0x2c) = g_7f4c04;
				*(int *)(msg + 0x30) = g_7f4c08;
				*(unsigned short *)(msg + 0x34) = g_7f4c0c;
				*(unsigned char *)(msg + 0x36) = 2;
				*(int *)(msg + 0x58) = *(int *)(r + 1);
				*(unsigned char *)(msg + 0xb0) = 0;
				query = (unsigned char *)(lpGebaeudePROT + (unsigned char)*(unsigned char *)r * 0x24d);
				*(int *)(msg + 0x5c) = (gm_RandomMod(0x10) & 0xffff) - *(unsigned char *)(query + 0x247) * 3 + 0x14;
				fcn_004c5530(msg);
			}
			if (model != 0 && v10 == 0) {
				fcn_00455350((char *)model, (char *)model + 0x4c, pos);
				pos[0] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[0] - g_664154;
				pos[1] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[1];
				pos[2] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[2] - g_664154;
				color[3] = 0x3f;
				color[2] = 0xc0;
				color[1] = 0xc0;
				color[0] = 0xc0;
				fcn_00418000(v10, pos, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f, 140.0f, 35.0f,
					pos + 4, 400, 6, *(int *)color);
				fcn_004185a0(v10, pos, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f, 4.0f, 7.0f, 8.0f,
					*(int *)color);
				fcn_00417d00(v10, pos, (int)(v24 * g_662c98), v24 * g_665ec0, v24 * g_662cf8,
					20.0f, 60.0f, 0x50);
			}
		}
		*(int *)(p + 0x52) = g_7f4c00;
		*(int *)(p + 0x56) = g_7f4c04;
		*(int *)(p + 0x5a) = g_7f4c08;
		*(unsigned short *)(p + 0x5e) = g_7f4c0c;
		fcn_00500bb0((void *)(p + 0x52), 0, gm_RandomMod(2) & 0xffff, 0);
		*(unsigned char *)(p + 0xc2) = *(unsigned char *)(p + 0xc2) + 1;
		fcn_004432d0(v10, 1);
		return;
		}
	case 6:
		r = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xc4));
		if (r == 0) {
			*(int *)(p + 0x70) = -1;
			return;
		}
		if (*(int *)(*(int *)(r + 0x184) + 0x128) != 0) {
			*(int *)(p + 0x52) = g_7f4c00;
			*(int *)(p + 0x56) = g_7f4c04;
			*(int *)(p + 0x5a) = g_7f4c08;
			*(unsigned short *)(p + 0x5e) = g_7f4c0c;
			fcn_00500bb0((void *)(p + 0x52), 0, 4, 0);
			goto label_56211d;
		}
		goto label_56148f;
	case 7:
		if (*(int *)(p + 0xc8) != -1 && !fcn_004c4450(*(int *)(p + 0xc8)))
			return;
		r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
		e = (unsigned char *)fcn_005463a0(1, 1, *(int *)(p + 0xcc));
		if (r == 0 || e == 0 || *(int *)(e + 0xd4) != *(int *)(p + 4) || *(int *)(p + 0xc8) == -1)
			goto label_56148f;
		query = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xcc));
		hand = (unsigned char *)fcn_004c4480(*(int *)(p + 0xc8));
		if (hand != 0 && query != 0)
			fcn_004c58b0(*(int *)hand, *(int *)(query + 4));
		*(int *)(p + 0x70) = 8;
		fcn_00500bb0((void *)(p + 0x52), 0, 10, 0);
		return;
	case 8:
		r = (unsigned char *)fcn_005463a0(1, 1, *(int *)(p + 0xcc));
		if (r == 0) {
			*(int *)(p + 0x70) = -1;
			return;
		}
		if (*(int *)(r + 0xd4) != *(int *)(p + 4)) {
			fcn_004c5da0(*(int *)(p + 0xc4), *(int *)(p + 0x10), -1, 0, 1, g_6a6560);
			*(int *)(p + 0x52) = g_7f4c00;
			*(int *)(p + 0x56) = g_7f4c04;
			*(int *)(p + 0x5a) = g_7f4c08;
			*(unsigned short *)(p + 0x5e) = g_7f4c0c;
			fcn_00500bb0((void *)(p + 0x52), 0, 4, 0);
			*(int *)(p + 0x70) = 6;
			return;
		}
		fcn_00500bb0((void *)(p + 0x52), 0, 6, 0);
		return;
	case -2:
	case -1:
		if (*(int *)(p + 0xc4) != -1)
			fcn_004c57e0(*(int *)(p + 0xc4), 1);
		fcn_00546190(p);
		return;
	default:
		return;
	}
label_56148f:
	*(int *)(p + 0xc4) = -1;
	*(int *)(p + 0x70) = -1;
	return;
label_561d51:
	*(int *)(p + 0x70) = -1;
	return;
label_56211d:
	*(int *)(p + 0x70) = 6;
	return;
}
unsigned char _dpad_6f2578[517488];
