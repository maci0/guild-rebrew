int __cdecl CountDisplayCounters(void);
int __cdecl d2_MeasureTextWidth(char*, int);
void __cdecl d2_DestroyElement(int);
int __cdecl d2_CreateElement(int, int, int);
void __cdecl d2_PositionControl(int, int, int);
typedef struct List0474cf0 {
	char pad0[0x28];
	int* ids;
	int count;
} List0474cf0;
typedef struct Slot0474cf0 {
	char pad0[0xc];
	struct Item0474cf0* item;
	char pad10[0x2c];
	int active;
	List0474cf0* list;
	char pad44[0x2b0];
} Slot0474cf0;
typedef struct Item0474cf0 {
	int pad0;
	int x;
	int y;
	char padc[0xc];
	int x18;
	int x1c;
	char pad20[8];
	unsigned char flags;
	char pad29[3];
	char text[0x100];
	int x12c;
	char pad130[4];
	int slot;
	int font;
} Item0474cf0;

extern int d2_Controls;
extern int tp_d2_SelectedControl;
extern int g_100f1cc;
extern int g_100f898;
extern int g_100f89c;
extern int g_67d8ec;
extern int g_67d3b0;

/* Selects one GUI pool record */
/* ADDRESS: GOLDTL 0x00474cf0 */
void __cdecl d2_SelectControl(int slot)
{
	Item0474cf0* it;
	Slot0474cf0* slots;
	List0474cf0* list;
	int i;
	int y;
	Item0474cf0* selected;

	slots = *(Slot0474cf0**) &d2_Controls;
	it = slots[slot].item;
	if (*(Item0474cf0**) &tp_d2_SelectedControl == it) {
		return;
	}
	if (*(Item0474cf0**) &tp_d2_SelectedControl != 0) {
		slots[(*(Item0474cf0**) &tp_d2_SelectedControl)->slot].active = 0;
		slots = *(Slot0474cf0**) &d2_Controls;
	}
	*(Item0474cf0**) &tp_d2_SelectedControl = it;
	slots[it->slot].active = 1;
	selected = *(Item0474cf0**) &tp_d2_SelectedControl;
	list = (*(Slot0474cf0**) &d2_Controls)[selected->slot].list;
	i = 0;
	while (list != 0 && i < list->count) {
		if (list->ids[i] == it->slot) {
			g_100f1cc = i;
		}
		i++;
	}
	it = selected;
	if ((it->flags & 0x40) &&
	    it->x18 == 0 &&
	    it->x1c == 0 &&
	    CountDisplayCounters() == 0 &&
	    it->x12c == 0) {
		it->x12c = -1;
		it = *(Item0474cf0**) &tp_d2_SelectedControl;
	}
	if ((it->flags & 2) &&
	    it->x18 != 0) {
		it->x12c = 1;
		it = *(Item0474cf0**) &tp_d2_SelectedControl;
	}
	if ((it->flags & 1) != 0) {
		g_100f898 =
		    d2_MeasureTextWidth(it->text, it->font) +
		    (*(Item0474cf0**) &tp_d2_SelectedControl)->x;
		g_100f89c = (*(Item0474cf0**) &tp_d2_SelectedControl)->y;
		y = g_100f89c - 7;
		if (g_67d8ec == -1) {
			g_67d8ec = d2_CreateElement(
			    (short) g_100f898, (short) y,
			    g_67d3b0 + 8);
			return;
		}
		d2_PositionControl(g_100f898, y, g_67d8ec);
		return;
	}
	if (g_67d8ec != -1) {
		d2_DestroyElement(g_67d8ec);
		g_67d8ec = -1;
	}
}

