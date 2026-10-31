
extern int g_772514;
extern int g_14ab694;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern unsigned char g_773d75;
extern char g_7f4ca0[];

int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_00472830(int, int, int, void*, void*, void*);
void __cdecl fcn_00533f40(int, int, int, int);
int __cdecl io_AppendText();
int __cdecl fcn_00533a60(int, int, int*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0046f280(int);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_0050d640(int, char*, unsigned int, char**);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_0050dd00(int, int*, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_005a4bb0(char*);
void __cdecl fcn_005a4960(char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005a4e00 */
void __cdecl fcn_005a4e00(char* a0)
{
	int items[16][3];
	int ids[16];
	char* out[16];
	int tmp[8];
	int v1;
	int v2;
	int v3;
	int h;
	int i;
	int j;
	int n;
	int count;
	int sum;
	int v;
	int first;
	char* p;

	for (i = 0; i < 16; i++) {
		items[i][0] = -1;
		items[i][1] = -1;
		items[i][2] = 0;
	}
	d2_SetOverlayAnimation(0, 0);
	h = fcn_00470820(0, 0, (char*) 0x6aac2c);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_00533dc0(g_772514, 0x73b, 0x73f);
	fcn_00533f40(0x206, 0x167, g_772514,
	    fcn_00472830(h, 2, 0x78, &v3, &v2, &v1));
	*(int*) (0x10162e8 + g_772514 * 0x3cc) = 0xe;
	*(int*) (0x10162ec + g_772514 * 0x3cc) = 0x18;
	*(int*) (0x10162f0 + g_772514 * 0x3cc) = 0xe;
	*(int*) (0x10162f4 + g_772514 * 0x3cc) = 0xe;
	d2_SetForm(h, 1);
	io_AppendText(0x18d9);
	d2_SetForm(h, 3);
	fcn_00533a60(g_772514, 0, tmp, 1, g_14ab694);
	first = 1;
	while (fcn_005373e0((void*) fcn_005a4e00, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (first) {
			d2_SetForm(h, 2);
			for (i = 0; i < 16; i++) {
				if (items[i][0] != -1) {
					fcn_0046f280(items[i][0]);
					fcn_0046b2b0(items[i][1]);
					items[i][0] = -1;
					items[i][1] = -1;
					items[i][2] = 0;
				}
			}
			io_AppendText(0x6811b0);
			n = fcn_0050d640(*(unsigned short*) (a0 + 0x27), a0, 0xffff, out);
			for (i = 0; i < 16; i++) {
				ids[i] = -1;
			}
			count = 1;
			for (j = 0; j < n; j++) {
				v = *(int*) (out[j] + 0xb0);
				for (i = 0; i < count; i++) {
					if (*(int*) (g_7f4ca0 + 4 + ids[i] * 0x21c) == v) {
						break;
					}
					if (ids[i] == -1) {
						p = gm_LookupEntityRecordById(v);
						if (p != 0) {
							ids[i] = *(unsigned short*) p;
							count++;
						}
						break;
					}
				}
			}
			d2_SetForm(h, 2);
			io_AppendText(0x18de,
			    *(unsigned short*) (0x8680b4 + g_773d75 * 0x2f4) * 2 + 0x9a8);
			if (count - 1 == 0) {
				io_AppendText(0x48d);
			}
			fcn_0050dd00(count - 1, ids, 0);
			for (i = 0; i < count - 1; i++) {
				v = fcn_0050d640(*(unsigned short*) (a0 + 0x27), a0,
				    ids[i], out);
				sum = 0;
				for (j = 0; j < v; j++) {
					sum += *(int*) (out[j] + 0xb4);
				}
				items[i][0] = fcn_00472250(h, 2,
				    io_AppendText(0x18df, ids[i], v, sum));
			}
		}
		first = 0;
		if (g_100f1dc == 2) {
			if (g_67d370 == tmp[0]) {
				fcn_005a4bb0(a0);
			}
			else {
				for (i = 0; i < count - 1; i++) {
					if (g_67d370 == items[i][0]) {
						fcn_005a4960(a0, ids[i]);
						first = 1;
					}
				}
			}
		}
	}
	fcn_00471e30(h);
	fcn_00532ef0();
}
