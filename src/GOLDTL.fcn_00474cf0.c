int __cdecl CountDisplayCounters(void);
int __cdecl fcn_0046b520(char*, int);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_00469c30(int, int, char*);
void __cdecl fcn_00469c40(int, int, int);

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

/* ADDRESS: GOLDTL 0x00474cf0 */
/* Selects one GUI pool record: clears the previous selection, marks the new
 * one, stores its index when its id appears in the owner's id list, refreshes
 * the display counter flags and reports the record's screen placement. */
void __cdecl fcn_00474cf0(int slot)
{
	Item0474cf0* it;
	List0474cf0* list;
	int i;
	int y;

	it = (*(Slot0474cf0**) 0x1015ea0)[slot].item;
	if (*(Item0474cf0**) 0x7725d0 == it) {
		return;
	}
	if (*(Item0474cf0**) 0x7725d0 != 0) {
		(*(Slot0474cf0**) 0x1015ea0)[(*(Item0474cf0**) 0x7725d0)->slot].active = 0;
	}
	*(Item0474cf0**) 0x7725d0 = it;
	(*(Slot0474cf0**) 0x1015ea0)[it->slot].active = 1;
	list = (*(Slot0474cf0**) 0x1015ea0)[(*(Item0474cf0**) 0x7725d0)->slot].list;
	i = 0;
	while (list != 0 && i < list->count) {
		if (list->ids[i] == it->slot) {
			*(int*) 0x100f1cc = i;
		}
		i++;
	}
	if (((*(Item0474cf0**) 0x7725d0)->flags & 0x40) &&
	    (*(Item0474cf0**) 0x7725d0)->x18 == 0 &&
	    (*(Item0474cf0**) 0x7725d0)->x1c == 0 &&
	    CountDisplayCounters() == 0 &&
	    (*(Item0474cf0**) 0x7725d0)->x12c == 0) {
		(*(Item0474cf0**) 0x7725d0)->x12c = -1;
	}
	if (((*(Item0474cf0**) 0x7725d0)->flags & 2) &&
	    (*(Item0474cf0**) 0x7725d0)->x18 != 0) {
		(*(Item0474cf0**) 0x7725d0)->x12c = 1;
	}
	if (((*(Item0474cf0**) 0x7725d0)->flags & 1) != 0) {
		*(int*) 0x100f898 =
		    fcn_0046b520((*(Item0474cf0**) 0x7725d0)->text,
				 (*(Item0474cf0**) 0x7725d0)->font) +
		    (*(Item0474cf0**) 0x7725d0)->x;
		*(int*) 0x100f89c = (*(Item0474cf0**) 0x7725d0)->y;
		y = *(int*) 0x100f89c - 7;
		if (*(int*) 0x67d8ec == -1) {
			*(int*) 0x67d8ec = fcn_00469c30(
			    *(int*) 0x100f898, y,
			    (char*) (*(int*) 0x67d3b0 + 8));
			return;
		}
		fcn_00469c40(*(int*) 0x100f898, y, *(int*) 0x67d8ec);
		return;
	}
	if (*(int*) 0x67d8ec != -1) {
		fcn_0046b2b0(*(int*) 0x67d8ec);
		*(int*) 0x67d8ec = -1;
	}
}
