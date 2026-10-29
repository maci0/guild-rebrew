int __cdecl fcn_0046e940(int x, int y, int w, int h, int a5);
void __cdecl fcn_00472900(int i, int v);
int __cdecl fcn_005373e0(void* fn, int line);
int __cdecl fcn_00519190(int fmt, ...);
float __cdecl eval_ObjektPreis2Credits(int id, int pct);
int __cdecl fcn_005b0f00(void* win);
void __cdecl fcn_0046f280(int);

extern char g_1015f40[];
extern char* lpObjektePROT;
extern int g_14ce8e0;
extern int g_774654;
extern int g_772514;

typedef struct
{
	unsigned short f00;
	char pad02[2];
	int f04;
	char pad08[8];
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	char pad28[0x10];
	float f38;
	char pad3c[0x44];
} Rec80;
/* SIZE 0x80 */

/* ADDRESS: GOLDTL 0x005b39c0 */
void __cdecl fcn_005b39c0(void)
{
	Rec80* rec;
	char* save;
	char* base;
	int idx;
	int n;
	int id;
	int slot;

	idx = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	fcn_00472900(*(int*) (g_1015f40 + idx * 0x3cc + 0x27c), 0x54);
	if (fcn_005373e0((void*) 0x5b39c0, 0x657c7) != 0) {
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			g_772514 = idx;
			fcn_00519190(0x6811b0);
			save = (char*) 0x85abac;
			base = (char*) 0x868060;
			do {
				if (*base == 0) {
					break;
				}
				fcn_00519190(0x6ab848, base);
				fcn_00519190(0x6ab834);
				rec = (Rec80*) (save - 0x1c);
				n = 0x55;
				do {
					if (rec->f00 != 0 && rec->f04 != 0) {
						id = rec->f00;
						slot = (int) lpObjektePROT + id * 0x40 + id;
						fcn_00519190(0x6ab804, slot + 1, (int) rec->f20, rec->f24,
							(int) rec->f38, (int) eval_ObjektPreis2Credits(id, 100), rec->f10,
							rec->f14, rec->f1c, rec->f18);
					}
					rec++;
					n--;
				} while (n);
				base += 0x2f4;
				save += 0x2a90;
			} while ((int) base < 0x868c30);
			fcn_005b0f00(g_1015f40 + idx * 0x3cc);
		} while (fcn_005373e0((void*) 0x5b39c0, 0x657c7) != 0);
	}
	fcn_0046f280(idx);
}
