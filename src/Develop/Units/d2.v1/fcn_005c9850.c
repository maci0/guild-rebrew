extern unsigned short g_774970;
extern int g_772514;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern void* g_1015ea0;
extern char g_7f4ca0[];

typedef struct {
	int out0;
	int out1;
	int out2;
	int ids[32];
	char tail[0x180];
} Rec_5c9850;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl fcn_005340f0(int);
int __cdecl fcn_005c9450(char*, int, int*);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
int __cdecl fcn_005c95d0(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c9850 */
void __cdecl fcn_005c9850(void)
{
	Rec_5c9850 rec;
	char* table;
	int obj;
	int n;
	int j;

	table = g_7f4ca0 + (unsigned short) g_774970 * 0x21c;
	obj = fcn_00470820(0, 0, (char*) 0x6ac94c);
	fcn_00471b60(obj);
	d2_SetForm(obj, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(obj, 1);
	io_AppendText(0xb2);
	d2_SetForm(obj, 2);
	n = fcn_005c9450(table, 0x80, rec.ids);
	d2_SetForm(obj, 0);
	fcn_00533f40(0x206, 0x167, g_772514, fcn_00472830(obj, 2), 0x100,
	    &rec.out1, &rec.out0, &rec.out2);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			for (j = 0; j < n; j++) {
				if (g_67d370 == rec.ids[j]) {
					fcn_005c95d0(((int*) g_1015ea0)[g_67d370 * 189 + 188]);
				}
			}
		}
	} while (fcn_005373e0(fcn_005c9850, 0x657c7) != 0);
	fcn_00471e30(obj);
}
