typedef struct {
	int ent;
	int a4;
	int a8;
	int ac;
	struct {
		int btn;
		int item;
	} s[6];
} Slot_5c6a10;

extern Slot_5c6a10 g_7774a0[32];
extern char* g_1015ea0;
extern char* g_99ec10;
extern unsigned char g_10161bc[];
extern int g_772514;
extern int g_775334;

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046b2b0(int);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00472380(int, int, int, int);
unsigned short* __cdecl fcn_00502850(void);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_00507c30(int);
void __cdecl fcn_00473690(int, int);
float __cdecl fcn_004ff040(int);

/* ADDRESS: GOLDTL 0x005c6a10 */
unsigned int __cdecl fcn_005c6a10(unsigned int a0, unsigned int a1)
{
	Slot_5c6a10* slot;
	unsigned short* item;
	int* list;
	int* p;
	int i;
	int j;
	int k;
	int h;
	int v;
	int built;

	built = 0;
	fcn_004727a0(a0, a1);
	g_775334 = 0;
	for (i = 0; i < 32; i++) {
		slot = g_7774a0 + i;
		if (!slot->ent)
			continue;
		g_775334++;
		for (list = (int*) 0x7e4260; list < (int*) 0x7e42e0; list++) {
			if (*list == slot->ent)
				break;
		}
		if (list >= (int*) 0x7e42e0) {
			slot->ent = 0;
			if (slot->a4 != -1) {
				fcn_0046b2b0(slot->a4);
				slot->a4 = -1;
			}
			if (slot->a8 != -1) {
				fcn_0046b2b0(slot->a8);
				slot->a8 = -1;
			}
			if (slot->ac != -1) {
				fcn_0046b2b0(slot->ac);
				slot->ac = -1;
			}
			continue;
		}
		g_772514 = slot->ac;
		for (j = 0; j < 6; j++) {
			if (slot->s[j].item != 0
			    && !fcn_00502cd0(*(int*) (slot->ent + 0x178), 1, 0, slot->s[j].item)) {
				fcn_0046b2b0(slot->s[j].btn);
				slot->s[j].btn = -1;
				slot->s[j].item = 0;
			}
		}
		g_772514 = slot->ac;
		fcn_00519190(0x6ac790, *(unsigned short*) slot->ent,
			(int) (fcn_004ff040(slot->ent) * 100.0));
		fcn_00519190(0x16ac);
		fcn_00534160(0x50, 0x16, *(unsigned char*) (slot->ent + 0x83), 0x4f1);
		fcn_00519190(0x16ad);
		fcn_00534160(0x50, 0x25, *(unsigned char*) (slot->ent + 0x82), 0x4f1);
		item = fcn_00502cd0(*(int*) (slot->ent + 0x178), 1, 5);
		while (item) {
			if (*(char*) (g_99ec10 + *item * 0x41) != '\t') {
				for (j = 0; j < 6; j++) {
					if (slot->s[j].item == *item)
						break;
				}
				if (j < 6)
					goto present;
				fcn_004727a0(a0, a1);
				for (j = 0; j < 6; j++) {
					if (!slot->s[j].item)
						break;
				}
				if (j < 6) {
					slot->s[j].btn = fcn_00466ee0(j * 0x36 + 0x50, 0x28 + i * 0x78,
						*item + 0xdf, 10, g_772514);
					slot->s[j].item = *item;
				}
present:
				v = fcn_00471f80(slot->s[j].btn);
				fcn_00472380(slot->s[j].btn, 0, *(int*) ((char*) item + 0xe), v);
			}
			item = fcn_00502850();
		}
	}
	for (list = (int*) 0x7e4260; list < (int*) 0x7e42e0; list++) {
		if (!*list)
			continue;
		k = fcn_00507c30(*(unsigned char*) (*list + 0x165));
		if (k < 10 || k > 12)
			continue;
		for (i = 0; i < 32; i++) {
			if (g_7774a0[i].ent == *list)
				break;
		}
		if (i < 32)
			continue;
		for (i = 0; i < 32; i++) {
			if (!g_7774a0[i].ent)
				break;
		}
		if (i >= 32)
			continue;
		fcn_004727a0(a0, a1);
		g_7774a0[i].ent = *list;
		h = fcn_0046f740(0, i * 0x78, 0x74c, g_772514);
		g_7774a0[i].a8 = h;
		*(int*) (g_1015ea0 + h * 0x2f4 + 0x5c) = 1;
		g_7774a0[i].a4 = fcn_0046f740(0x10, i * 0x78 + 5,
			*(int*) (g_7774a0[i].ent + 0x18c), g_772514);
		h = fcn_0046f100(0x40, i * 0x78, 0xb4, 0x50, 0x10, g_772514);
		g_7774a0[i].ac = h;
		fcn_00472900(*(int*) (g_10161bc + h * 0x3cc), 0x54);
		fcn_00519190(0x16ab, *(unsigned short*) g_7774a0[i].ent,
			*(unsigned char*) (g_7774a0[i].ent + 0x83));
	}
	for (i = 0; i < 32; i++) {
		if (!g_7774a0[i].ent)
			continue;
		for (j = 0; j < 6; j++) {
			if (g_7774a0[i].s[j].btn != -1 && fcn_00471f80(g_7774a0[i].s[j].btn)) {
				fcn_00473690(g_7774a0[i].s[j].item + 0xdf,
					fcn_00471f80(g_7774a0[i].s[j].btn));
				built = 1;
			}
		}
	}
	return built;
}
