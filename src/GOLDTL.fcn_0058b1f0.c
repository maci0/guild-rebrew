int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void* __cdecl fcn_004f18d0(int, char*, void*, void*, int);
char __cdecl fcn_004f1790(int, int*);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0057b9d0(char*, int, int);
void __cdecl fcn_0046c310(int);

extern void* g_1015ea0;
extern char g_1016198[];
extern int g_665f68[4];
extern int g_665f58[4];
extern char g_6811b0[];

typedef struct SlotItem {
	int id;                     /* 0x00 */
	int flag;                   /* 0x04 */
} SlotItem;

typedef struct DialogEntry {
	int btn;                    /* 0x00 */
	SlotItem* item;             /* 0x04 */
	int id;                     /* 0x08 */
	char kind;                  /* 0x0c */
	char pad_0d[3];
} DialogEntry;

typedef struct DialogState {
	int handle;                 /* 0x00 */
	int filter;                 /* 0x04 */
	int slot;                   /* 0x08 */
	char pad_0c[0x08];
	int owner;                  /* 0x14 */
	char pad_18[0x18];
	int type;                   /* 0x30 */
	DialogEntry entries[16];    /* 0x34 */
	int selected;               /* 0x134 */
} DialogState;

/* Fills the slot-detail dialog: one row per occupied slot of the requested
 * type, marks the selected row and clears the unused rows. */

/* ADDRESS: GOLDTL 0x0058b1f0 */
void __cdecl fcn_0058b1f0(char* a0, DialogState* st, unsigned int type)
{
	SlotItem* item;
	DialogEntry* de;
	int saved;
	int count;
	int i;
	int y;
	int mark;
	int id1;
	int id2;
	int selected;

	saved = 0;
	if (type == (unsigned int) st->type) {
		saved = *(int*) (g_1016198 + st->slot * 0x3cc);
	}
	fcn_004727a0(st->handle, 2);
	fcn_00519190(0x6811b0);
	fcn_004727a0(st->handle, 4);
	fcn_00519190(0x6811b0);
	selected = type;
	fcn_00533f40(0, 0, st->owner, st->slot, 0x35, &id2, &id1, &selected);

	item = (SlotItem*) fcn_004f18d0(0, a0, 0, 0, st->type);
	count = 0;
	y = 2;
	de = st->entries;
	while (item != 0) {
		de->item = item;
		de->id = item->id;
		de->kind = fcn_004f1790(*(int*) (a0 + 0x65), (int*) item);
		if (item->flag != -1) {
			de->btn = fcn_0046f740(1, y, g_665f68[st->type], st->slot);
		} else {
			de->btn = fcn_0046f740(1, y, g_665f58[st->type], st->slot);
		}
		mark = fcn_0057b9d0(a0, item->id, de->kind);
		if (mark != 0) {
			fcn_0046f740(0xf, y + 7, 0x7de, st->slot);
		}
		*(int*) ((char*) g_1015ea0 + 0x5c + de->btn * 0x2f4) = 1;
		*(int*) ((char*) g_1015ea0 + 0x1d0 + de->btn * 0x2f4) = 3;
		item = (SlotItem*) fcn_004f18d0(0, a0, item, 0, st->type);
		count++;
		y += 0x35;
		de++;
	}
	if (count <= st->selected) {
		st->selected = 0;
	}
	*(int*) ((char*) g_1015ea0 + 0x3c + st->selected * 0x2f4) = 1;
	*(int*) ((char*) g_1015ea0 + 0x38 + st->entries[st->selected].btn * 0x2f4) = 1;
	for (i = count; i < 0x10; i++) {
		st->entries[i].btn = -1;
		st->entries[i].item = 0;
		st->entries[i].id = 0;
		st->entries[i].kind = -1;
	}
	*(int*) (g_1016198 + st->slot * 0x3cc) = saved;
	*(int*) (g_1016198 + st->slot * 0x3cc + 0x1c) = 0x35;
	fcn_0046c310(st->slot);
}
