typedef struct {
	char pad0[0xc];
	int f_c;
} Screen;
// SIZE 0x10

extern char* g_77255c;
extern int g_772514;
extern char* g_1015ea0;
extern char g_6b5c60[];
extern double g_662c38;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl fcn_00507e30(char*, int);
void __cdecl fcn_00534160(int, int, int, int);
float __cdecl fcn_004ff040(char*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_0046f940(int, char*);
int* __cdecl fcn_004ce610(char*);
void __cdecl fcn_00472680(int, int);

/* ADDRESS: GOLDTL 0x004d5740 */
void __cdecl fcn_004d5740(char* a0, int a1, int a2)
{
	char buf[0x100];
	int total;
	int i;
	int div;
	int id;
	int x;
	int y;
	int h;
	char* rec;
	int* p;
	float f;
	int v;

	total = 0;
	for (i = 0; i < 0x10; i++)
		if (*(int*) (a0 + i * 4) != -1)
			total++;
	div = (((Screen*) g_77255c)->f_c - 0x30) / (total + 1);
	for (i = 0; i < 0x10; i++) {
		id = *(int*) (a0 + i * 4);
		if (id == -1)
			continue;
		rec = gm_LookupEntityRecordIn32SlotTable(id);
		x = (i % 6 + 1) * div + a1;
		y = a2 + (i / 6) * 100;
		fcn_0046f740(x - 0x10, y, 0x5da, g_772514);
		fcn_0046f740(x - 4, y, *(int*) (rec + 0x18c), g_772514);
		f = (float) fcn_00507e30(rec, 3);
		fcn_00534160(x, y + 0x3c, (int) f, 0x4eb);
		h = d2_ShowTxt(x - 0x24, y - 0x11, g_6b5c60, g_772514);
		*(int*) (g_1015ea0 + h * 0x2f4 + 0x18) = 0x78;
		*(int*) (g_1015ea0 + h * 0x2f4 + 0x6c) = 1;
		*(int*) (g_1015ea0 + h * 0x2f4 + 0x84) = 0x56;
		io_FormatTextBuffer(buf, "%1N1 %i%", *(unsigned short*) rec,
			     (int) (fcn_004ff040(rec) * g_662c38));
		fcn_0046f940(h, buf);
		p = fcn_004ce610(rec);
		if (p != 0 && *p != 0) {
			v = fcn_0046f740(x + 0x28, y + 0xf, *p + 0xdf, g_772514);
			fcn_00472680(v, -2);
		}
		if (*(char*) (rec + 8) == 0) {
			v = (int) -(*(float*) (rec + 0x1c));
			if (*(int*) (rec + 0x24) == (float) v - 20.0) {
				fcn_0046f740(x, y + 6, 0x3b, g_772514);
			} else {
				fcn_0046f740(x, y + 6, 0x37, g_772514);
			}
		}
	}
}
