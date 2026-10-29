#pragma pack(push, 1)
typedef struct Kind50bec0 {
	char pad0[0x22];
	unsigned char cnt;
	unsigned short slot[0x40];
	char pad[0x24d - 0xa3];
} Kind50bec0;

typedef struct {
	char kind;
	char pad[0x40];
} Obj50bec0;
#pragma pack(pop)
// SIZE 0x24d, 0x41

extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x0050bec0 */
int __cdecl fcn_0050bec0(unsigned char* s, int* out)
{
	Kind50bec0* k;
	int n;
	int i;
	int w;

	n = 0;
	k = &((Kind50bec0*)lpGebaeudePROT)[*s];
	for (i = 0; i < 0x40; i++) {
		if (k->slot[i] == 0) {
			break;
		}
		w = k->slot[i] & 0x7fff;
		if (((Obj50bec0*)lpObjektePROT)[w].kind != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = w;
		}
	}
	return n;
}

/* ADDRESS: GOLD 0x00508cf0 */
/* ADDRESS: GOLDTL 0x0050bf30 */
int __cdecl fcn_0050bf30(unsigned char* s, unsigned short* key, int* out)
{
	Kind50bec0* k;
	Obj50bec0* o;
	int n;
	int i;
	int w;

	n = 0;
	k = &((Kind50bec0*)lpGebaeudePROT)[*s];
	for (i = 0; i < k->cnt; i++) {
		if ((unsigned short) (k->slot[i] & 0x7fff) == *key) {
			break;
		}
	}
	if (i >= k->cnt) {
		return 0;
	}
	for (i++; i < 0x40; i++) {
		if (k->slot[i] == 0) {
			break;
		}
		w = k->slot[i] & 0x7fff;
		o = &((Obj50bec0*)lpObjektePROT)[w];
		if (o->kind == 2 || o->kind == 6) {
			break;
		}
		if (o->kind != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = w;
		}
	}
	return n;
}
