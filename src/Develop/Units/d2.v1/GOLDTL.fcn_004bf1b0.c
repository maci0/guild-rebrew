extern char* g_1015ea0;
extern char* g_entity_type_table;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_772908;
extern int g_772900;
extern int g_774654;
extern int g_6816d8;
extern int g_14ce8e0;
extern int g_14b5e9c;
extern int g_14b5ea4;
extern char* g_14b5e88;
extern char* g_14b5e8c;
extern char s_68170c[];
extern char s_681718[];
extern int g_10058a0[];

void* __cdecl gm_SearchTable67(int);
char* __cdecl gm_FindRecordById(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471a30(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472830(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050dfd0(int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
void __cdecl d2_SetElementValue(int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_004bf000(unsigned short*, int, int, int, int, int, int, int*);
void __cdecl fcn_004bf150(int*);
void __cdecl fcn_004bf1a0(char*);
int __cdecl fcn_004bd9b0(char*);
int __cdecl fcn_004be340(char*);
void __cdecl fcn_004be360(void);
void __cdecl fcn_004be380(void);
void __cdecl fcn_004be3d0(int*, char*, int, int);
int __cdecl fcn_004bea00(char*, int);
unsigned int __cdecl fcn_004be560(char*, int, unsigned int);
unsigned int __cdecl fcn_004bec20(char*, int, unsigned int);
int __cdecl fcn_004bf3e0(int*);
void __cdecl fcn_004bfc70(int);

/* ADDRESS: GOLDTL 0x004bf1b0 */
void __cdecl fcn_004bf1b0(int* a0, int* a1)
{
	int counts[3] = { 1, 2, 3 };
	int ids[2];
	int icons[12];
	int labels[3];
	int nodeA[3][3];
	int nodeB[3][3];
	int* cur;
	int* node;
	char* rec;
	char* tbl;
	char* types;
	char* item;
	int h;
	int first;
	int value;
	int selA;
	int selB;
	int kind;
	int n;
	int i;
	int k;

	cur = 0;
	node = 0;
	tbl = (char*) gm_SearchTable67(a0[1]);
	rec = gm_FindRecordById(a0[0]);
	if (rec == 0 || tbl == 0) {
		return;
	}
	fcn_00471a30(a1[0], 0);
	h = fcn_00470820(0, 0, s_681718);
	fcn_00471b60(h);
	first = fcn_00472830(h, 2);
	fcn_00472830(h, 1);
	d2_SetForm(h, 1);
	fcn_00519190(s_68170c, *(unsigned short*) (tbl + 0x27), tbl);
	d2_SetForm(h, 3);
	fcn_00533a60(g_772514, 0, ids, 2, g_14b5e9c, g_14b5ea4);
	selA = ids[0];
	selB = ids[1];
	types = g_entity_type_table + *(unsigned char*) tbl * 0x24d;
	n = counts[*(unsigned short*) rec - 0x134];
	item = fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, 0x1dd);
	value = fcn_0050dfd0((int) item, 0);
	icons[0] = -1;
	icons[1] = -1;
	icons[2] = -1;
	labels[0] = -1;
	labels[1] = -1;
	labels[2] = -1;
	for (k = 0; k < 3; k++) {
		fcn_004bf1a0((char*) &nodeA[k][0]);
		fcn_004bf1a0((char*) &nodeB[k][0]);
	}
	fcn_0046f740(0x6e, 0x1a, *(unsigned short*) rec + 0x4ae, h);
	i = d2_ShowTxt(0x6e, 2, g_14b5e88, h);
	*(int*) (g_1015ea0 + i * 0x2f4 + 0x6c) = 1;
	*(int*) (g_1015ea0 + i * 0x2f4 + 0x18) = 0xcd;
	fcn_0046f740(0x6e, 0x88, *(unsigned short*) rec + 0x4ae, h);
	i = d2_ShowTxt(0x6e, 0x70, g_14b5e8c, h);
	*(int*) (g_1015ea0 + i * 0x2f4 + 0x6c) = 1;
	*(int*) (g_1015ea0 + i * 0x2f4 + 0x18) = 0xcd;
	if (n >= 1) {
		icons[3] = 0x51;
		icons[4] = 0;
		icons[5] = 0;
		icons[6] = 0x30;
		icons[7] = 0x71;
		icons[8] = 0;
		icons[9] = 0x11;
		icons[10] = 0x52;
		icons[11] = 0x93;
		for (i = 0; i < n; i++) {
			k = icons[3 + i + (*(unsigned short*) rec - 0x134) * 3] + 0x6e;
			icons[i] = fcn_0046f740(k, 0x22, 0x525, h);
			*(int*) (g_1015ea0 + icons[i] * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + icons[i] * 0x2f4 + 0x1d0) = 3;
			labels[i] = fcn_0046f740(k, 0x90, 0x525, h);
			*(int*) (g_1015ea0 + labels[i] * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + labels[i] * 0x2f4 + 0x1d0) = 3;
		}
	}
	while (fcn_005373e0(fcn_004bf1b0, 0x657c7) != 0) {
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && g_67d370 == selA)) {
			g_774654 = 1;
		}
		if (g_772908 != 0 && selB != -1) {
			k = fcn_004be340((char*) g_772908) > 1;
		}
		else {
			k = 1;
		}
		fcn_00472640(selB, k);
		for (i = 0; i < 3; i++) {
			if (nodeA[i][1] == -1 && a0[2 + i * 2] != 0) {
				fcn_004bf000((unsigned short*) rec, (int) item, a0[2 + i * 2], i, 0, 0, first, &nodeA[i][0]);
				k = a0[3 + i * 2];
				if (k < 1) {
					k = 1;
				}
				d2_SetElementValue(nodeA[i][1], 1, value, k);
			}
			if (nodeA[i][2] != -1) {
				d2_SetElementValue(nodeA[i][2], 0, value, fcn_00471f80(nodeA[i][1]));
			}
		}
		for (i = 0; i < 3; i++) {
			if (nodeB[i][1] == -1 && a0[8 + i * 2] != 0) {
				fcn_004bf000((unsigned short*) rec, (int) item, a0[8 + i * 2], i, 0, 0x6e, first, &nodeB[i][0]);
				k = a0[9 + i * 2];
				if (k < 1) {
					k = 1;
				}
				d2_SetElementValue(nodeB[i][1], 1, value, k);
			}
			if (nodeB[i][2] != -1) {
				d2_SetElementValue(nodeB[i][2], 0, value, fcn_00471f80(nodeB[i][1]));
			}
		}
		if (g_100f1dc != -1) {
			for (i = 0; i < 3; i++) {
				if (icons[i] != -1 && icons[i] == g_67d370) {
					cur = &a0[2 + i * 2];
					node = &nodeA[i][0];
					kind = 1;
				}
			}
			for (i = 0; i < 3; i++) {
				if (labels[i] != -1 && labels[i] == g_67d370) {
					cur = &a0[8 + i * 2];
					node = &nodeB[i][0];
					kind = 2;
				}
			}
			if (cur != 0) {
				fcn_00471a30(h, 0);
				if (kind == 1) {
					n = *cur;
					if (*types == 0x0a) {
						k = (int) fcn_004bec20(tbl, 1, n);
					}
					else {
						k = (int) fcn_004be560(tbl, 1, n);
					}
					*cur = k;
					if (n != k) {
						fcn_004bf150(node);
					}
				}
				else {
					*cur = fcn_004bea00(rec, (int) g_772908);
				}
				fcn_00471a30(h, 1);
				cur = 0;
			}
			if (g_67d370 == selB) {
				k = fcn_004bf3e0(a0);
				if (k != -1) {
					fcn_004bfc70(k);
				}
				fcn_004be360();
				fcn_004be380();
				if (a0 == (int*) g_772908) {
					g_772908 = a0[0xf];
				}
				fcn_004bd9b0((char*) a0);
				for (i = 0; i < 8; i++) {
					if (g_10058a0[i * 2] != -1) {
						fcn_004bfc70(i);
					}
				}
				g_772900 = 0;
				fcn_004be360();
				a0 = (int*) g_772908;
				while (a0 != 0) {
					fcn_004be3d0(a1, rec, g_772908, (int) a0);
					a0 = (int*) a0[0xf];
				}
				fcn_004695a0(g_6816d8, 0);
				g_774654 = 1;
			}
		}
	}
	if (a0 != 0) {
		for (i = 0; i < 3; i++) {
			if (nodeA[i][1] != -1) {
				*(int*) ((char*) a0 + 0xc + i * 8) = fcn_00471f80(nodeA[i][1]);
			}
		}
		for (i = 0; i < 3; i++) {
			if (nodeB[i][1] != -1) {
				*(int*) ((char*) a0 + 0x24 + i * 8) = fcn_00471f80(nodeB[i][1]);
			}
		}
	}
	fcn_00471e30(h);
	fcn_00471a30(a1[0], 1);
}
unsigned char _dpad_772908[1032];
