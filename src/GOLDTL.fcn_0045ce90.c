/* SIZE 0x70 */
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	int pad4c;
	int x50;
	unsigned char flags;
	char pad55[0x5c - 0x55];
	unsigned char x5c;
	unsigned char x5d;
	char pad5e[2];
	int x60;
	int x64;
	int x68;
	int pad6c;
} Tex;

extern unsigned char g_6b7ff8;
extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_67bd2c;

int __cdecl fcn_0045be40(char* name);
void __cdecl fcn_00436ff0(int a1, int a2, void* a3, int a4, int a5, int a6);
void __cdecl fcn_0045ce20(Tex* a0);

/* ADDRESS: GOLDTL 0x0045ce90 */
void __cdecl fcn_0045ce90(Tex* a0)
{
	Tex* p;
	int obj;
	unsigned int i;
	unsigned char saved;

	if (a0 != 0 && a0->refs > 0) {
		if (a0->flags & 2) {
			a0 = (Tex*) g_104049c + a0->parent;
		}
		saved = g_6b7ff8;
		if (a0->x50 == 0 && a0->parent != 0 && a0->name[0] != '*') {
			obj = fcn_0045be40(a0->name);
			if (obj != 0) {
				g_6b7ff8 = (a0->flags & 0x20) ? 0 : saved;
				fcn_00436ff0(obj, a0->x60, &a0->x50, g_67bd2c, a0->x68, a0->x68);
				a0->x64 = (unsigned int) a0->x68 >> g_6b7ff8;
			}
		}
		fcn_0045ce20(a0);
		g_6b7ff8 = saved;
		if (a0->x5c > 1 && a0->x5d > 0) {
			p = (Tex*) g_104049c;
			for (i = 0; i < g_10404a0; i++, p++) {
				if (p->refs > 0 && p->id == a0->id && p->x5d > 0) {
					fcn_0045ce90(p);
				}
			}
		}
	}
}
