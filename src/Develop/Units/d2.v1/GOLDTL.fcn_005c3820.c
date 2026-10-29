extern char* g_77255c;
extern char* g_1015ea0;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;

void* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_0050c7d0(int, int);
int __cdecl fcn_0050c710(unsigned char*, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0046f9b0(int, char*);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_00526120(void*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471a30(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_SetElementValue(int, ...);

/* ADDRESS: GOLDTL 0x005c3820 */
void __cdecl fcn_005c3820(unsigned char* a0, unsigned char* a1)
{
	int table[37] = { 1, 2, 0xb, 0xc, 9, 5, 6, 3, 4, 0xa, 0xd, 0xe, 0xf,
		0x10, 0x11, 7, 8, 0 };
	int elems[37];
	int wins[37];
	char buf[1024];
	int count;
	int window;
	int elem;
	int id;
	int step;
	int height;
	int i;
	int entry;
	int type;

	count = 0;
	id = *(int*) (a0 + 1);
	for (i = 0; i < 0x24; i++) {
		table[i] = i + 1;
	}
	for (i = 0; i < 0x25; i++) {
		elems[i] = -1;
	}
	table[0x24] = 0;
	window = fcn_00470820(0, 0, "techtree\\auswirkungen");
	fcn_00471b60(window);
	fcn_00473a90(0, 0);
	d2_SetForm(window, 1);
	fcn_00519190(0x17e0, a0);
	d2_SetForm(window, 3);
	elem = fcn_00472250(window, 3, fcn_00519190(0x17e1));
	d2_SetForm(window, 2);
	entry = table[0];
	if (entry != 0) {
		for (i = 0; table[i] != 0; i++) {
			if (fcn_0050c7d0(a0[0], table[i]) != 0) {
				count++;
			}
		}
	}
	step = (int) (10.0f / count * 24.0f);
	height = (*(int*) (g_77255c + 0x10) - step * count) / 2 + 0xe;
	if (entry != 0) {
		for (i = 0; table[i] != 0; i++) {
			if (fcn_0050c7d0(a0[0], table[i]) != 0) {
				window = fcn_0046f740(0, height, 2, g_772514);
				wins[i] = window;
				*(int*) (g_1015ea0 + window * 0x2f4 + 0x1d0) = 3;
				*(int*) (g_1015ea0 + window * 0x2f4 + 0x84) = 0x55;
				fcn_0051af00(buf, "%s:", *(unsigned int*) (table[i] * 8 + 0x14a9180));
				fcn_0046f9b0(window, buf);
				*(int*) (g_1015ea0 + window * 0x2f4 + 0x5c) = 1;
				if (table[i] == 3) {
					type = 6;
				}
				else if (table[i] == 0x24) {
					type = 4;
				}
				else {
					type = fcn_0050c7d0(a0[0], table[i]);
				}
				elem = fcn_004677e0(0x140, height, 0x82, 0, type, 0x6f, 0x56, g_772514);
				elems[i] = elem;
				d2_SetElementValue(elem, 0, type, 0, 0);
				height += step;
			}
			else {
				wins[i] = -1;
			}
		}
	}
	g_100f1dc = -1;
	for (;;) {
		if ((a1[0x5b] & 4) != 0 || gm_SearchTable67(id) == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (g_67d370 == elem) {
				g_774654 = 1;
			}
		}
		if (g_100f1dc != -1 && entry != 0) {
			for (i = 0; table[i] != 0; i++) {
				if (wins[i] != -1 && g_67d370 == wins[i]) {
					fcn_0051af00(buf, "$Z$[%s$]$N%s", table[i] * 2 + 0xf98,
					    table[i] * 2 + 0xf99);
					fcn_00471a30(window, 0);
					fcn_00526120(buf, 0x10);
					fcn_00471a30(window, 1);
				}
			}
		}
		if (entry != 0) {
			for (i = 0; table[i] != 0; i++) {
				if (fcn_0050c7d0(a0[0], table[i]) != 0 && elems[i] != -1) {
					if (table[i] == 3) {
						type = 6;
					}
					else if (table[i] == 0x24) {
						type = 4;
					}
					else {
						type = fcn_0050c7d0(a0[0], table[i]);
					}
					fcn_0050c710((unsigned char*) a0, table[i], 0);
					d2_SetElementValue(elems[i], 0, type,
					    fcn_0050c710((unsigned char*) a0, table[i], 1),
					    fcn_0050c710((unsigned char*) a0, table[i], 0));
				}
			}
		}
		if (fcn_005373e0((void*) 0x5c3820, 0x677c7) == 0) {
			fcn_00471e30(window);
			return;
		}
	}
}
