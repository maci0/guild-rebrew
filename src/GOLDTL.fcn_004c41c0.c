// FUNCTION: GOLD 0x004c3850
// SIZE: 139
// FUNCTION: GOLDTL 0x4c41c0
// SIZE: 139

#pragma pack(1)
typedef struct node99 {
	char f0;
	char f1;
	char f2;
	char f3;
	int f4;
	int f8;
	int fc;
	unsigned short f10;
	char data[0x7f];
	struct node99* prev;
	struct node99* next;
} node99;
// SIZE 0x99
#pragma pack()

extern node99* g_aed324;

int __cdecl fcn_004c41c0(node99* n)
{
	node99* p;
	node99* q;
	int len;
	int off;

	if (n->f0 == 7 || n->fc == 0)
		return 1;
	for (p = g_aed324; p != 0; p = p->next) {
		if (p->f3 == n->f3 && p->f8 == n->fc)
			break;
	}
	if (p == 0)
		return 0;
	len = p->f10;
	q = p;
	for (off = 0x7e; off < len; off += 0x80) {
		for (p = g_aed324; p != 0; p = p->next) {
			if (p->f3 == q->f3 && p->f8 == q->fc)
				break;
		}
		if (p == 0)
			return 0;
		q = p;
	}
	return 1;
}
