/* AI step: upgrade a guild workshop. Picks the workshop kind for the entity's
 * profession, then tries an upgrade order, a repair/expand order or a sale
 * order, writing the two 0x18-byte order records on success. */

typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	int e;
} Blk24;
// SIZE 0x18

/* SIZE 0x24d */
typedef struct {
	char pad[0x247];
	unsigned char count;
	unsigned char max;
	char pad249[0x24d - 0x249];
} BuildingRow;

extern unsigned char g_773d75;
extern unsigned char* lpGebaeudePROT;
extern float g_6628bc;
extern float g_6628cc;
extern float g_6628d8;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, unsigned char);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);
int __cdecl fcn_004a48a0(char*, int);
int __cdecl fcn_004a4fb0(int* a, int* b, char* q, int c);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_0050d320(char*, unsigned char);
float __cdecl fcn_0050bb50(int, unsigned char);

/* ADDRESS: GOLDTL 0x004a04b0 */
int __cdecl ai_StartUpgradeZunft(int a0, char* e, int a2, Blk24* o1, Blk24* o2)
{
	Blk24 d;
	Blk24 c;
	Blk24 a;
	Blk24 b;
	int t;
	int need;
	int val;
	int flag;
	int price;
	int r;
	char* w;
	char* item;
	BuildingRow* row;
	unsigned char k;
	char lvl;

	if (a2 != 0 || o1->kind != 0 || a0 != 0) {
		return 0;
	}
	k = e[0x169];
	if (k < 0x1e && k > 0x21) {
		return 0;
	}
	if (k == 0x1e) {
		w = gm_StartFilteredEntitySearch(1, 5, 0x17);
	} else if (k == 0x1f) {
		w = gm_StartFilteredEntitySearch(1, 5, 0x18);
	} else if (k == 0x20) {
		w = gm_StartFilteredEntitySearch(1, 5, 0x19);
	} else {
		w = gm_StartFilteredEntitySearch(1, 5, 0x1a);
	}
	if (w == 0) {
		return 0;
	}
	item = fcn_00502cd0(*(int*) (w + 0x5d), 2, 6, 0, 0x142);
	price = fcn_0050b810(*(int*) (item + 0x14), g_773d75);
	lvl = w[0x5c];
	if (lvl < gm_RandomMod(0x10) + 0x32 && !(w[0x5a] & 4)) {
		a.a = *(int*) (w + 1);
		a.kind = 4;
		a.b = 1;
		if (lvl < 0x21) {
			need = 0x32;
		} else {
			need = (lvl < 0x42) ? 0x1e : 10;
		}
		b.d = 1;
		b.a = *(int*) (item + 2);
		a.d = need;
		b.kind = 1;
		b.b = price;
		r = fcn_00495400(0xf, *(unsigned short*) e, 0, &a, &b);
		if (r != 0) {
			*o1 = a;
			*o2 = b;
			return r;
		}
		val = fcn_004a48a0(w, need);
		if (val > price) {
			flag = 1;
			goto sell;
		}
	}
	if (fcn_004a4fb0(&a2, &a0, w, 0)) {
		flag = 1;
		c.kind = 2;
		c.a = a2;
		c.b = flag;
		c.c = *(int*) (item + 2);
		c.d = 0x39;
		d.d = price;
		if (a0 != -1) {
			d.kind = flag;
			d.a = a0;
		} else {
			d.kind = 4;
			d.a = *(int*) (w + 1);
		}
		d.b = flag;
		d.e = 0;
		val = (int) fcn_0050bb50(a2, g_773d75);
		if (val < price) {
			goto sell;
		}
		r = fcn_00495400(0x39, *(unsigned short*) e, flag, &c, &d);
		if (r == 0) {
			return 0;
		}
		*o1 = c;
		*o2 = d;
		return r;
	}
	row = &((BuildingRow*) lpGebaeudePROT)[*(unsigned char*) w];
	if (w[0x5a] & 0x45) {
		return 0;
	}
	if (row->count >= row->max) {
		return 0;
	}
	flag = *(unsigned char*) w + 1;
	t = (int) (fcn_0050d170(flag) * g_6628d8);
	if (t < price) {
		o1->kind = 4;
		o1->a = flag;
		o1->b = 1;
		o1->c = *(int*) (w + 1);
		o2->kind = 1;
		o2->a = *(int*) (item + 2);
		o2->b = 1;
		return 0x39;
	}
	r = fcn_0050d320(e, g_773d75);
	if (r < 80000) {
		return 0;
	}
	a0 = r - 80000;
	if ((int) (a0 * g_6628cc) < t + 0x20) {
		return 0;
	}
	o1->kind = 1;
	o1->a = *(int*) (item + 2);
	o1->d = 1;
	o2->b = t + 0x20;
	o2->kind = 0x12;
	return 0x39;
sell:
	r = fcn_0050d320(e, g_773d75);
	if (r < 80000) {
		return 0;
	}
	val += 0x20;
	a0 = r - 80000;
	if ((int) (a0 * g_6628bc) < val) {
		return 0;
	}
	o1->kind = 1;
	o1->a = *(int*) (item + 2);
	o1->d = flag;
	o2->b = val;
	o2->kind = 0x12;
	return 0x39;
}
