int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00471e30(int);
void __cdecl fcn_004116d0(void);
int __cdecl fcn_005373e0(int, int);

extern void* g_1015ea0;
extern int g_772514;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;

typedef struct RouteItem {
	int value;                  /* 0x00 */
	int weight;                 /* 0x04 */
} RouteItem;

typedef struct RouteNode {
	char pad_00[0x08];
	RouteItem items[3];         /* 0x08 */
	char pad_20[0x1c];
	struct RouteNode* next;     /* 0x3c */
} RouteNode;

/* Builds the "choose good routing" dialog: one button per routed target of
 * every list node, plus an OK button, then pumps the frame delay until the
 * dialog closes and returns the picked target. */

/* ADDRESS: GOLDTL 0x004bea00 */
int __cdecl fcn_004bea00(int ctx, RouteNode* list)
{
	RouteNode* node;
	int entries[10];
	int values[24];
	int result;
	int count;
	int i;
	int menu;
	int entry;
	int active;
	int flag;
	int selected;
	char* slot;

	result = 0;
	count = 0;
	(void) ctx;
	for (node = list; node != 0; node = node->next) {
		for (i = 0; i < 3; i++) {
			if (node->items[i].value != 0 && node->items[i].weight > 0) {
				values[count] = node->items[i].value;
				count++;
			}
		}
	}
	menu = fcn_00470820(0, 0, (char*) 0x6816e8);
	fcn_00471b60(menu);
	fcn_004727a0(menu, 4);
	active = fcn_00472250(menu, 4, fcn_00519190(0x7d));
	fcn_004727a0(menu, 2);
	for (i = 0; i < count; i++) {
		entry = fcn_0046f740((i % 4) << 6, (i / 4) << 6, values[i] + 0xdf,
			g_772514);
		entries[i] = entry;
		slot = (char*) g_1015ea0 + entry * 0x2f4;
		*(int*) (slot + 0x5c) = 1;
		*(int*) (slot + 0x1d0) = 3;
		*(int*) (slot + 0x1e4) = 0x525;
	}
	values[count] = 0;
	entry = fcn_0046f740((count % 4) * 0x40 + 7, (count / 4) * 0x40 + 7, 0x527,
		g_772514);
	entries[count] = entry;
	slot = (char*) g_1015ea0 + entry * 0x2f4;
	*(int*) (slot + 0x5c) = 1;
	*(int*) (slot + 0x1d0) = 3;

	while (fcn_005373e0(0x4bea00, 0x657c7) != 0) {
		selected = g_67d370;
		flag = g_100f1dc;
		if (g_14ce8e0 != 0 || result != 0) {
			g_774654 = 1;
		} else if (flag != -1 && selected == active) {
			g_774654 = 1;
		}
		if (flag != -1) {
			for (i = 0; i <= count; i++) {
				if (selected == entries[i]) {
					result = values[i];
					break;
				}
			}
		}
	}
	fcn_00471e30(menu);
	fcn_004116d0();
	return result;
}
