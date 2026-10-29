#include <string.h>

/* SIZE 0x10 */
typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;

/* SIZE 0xc */
typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

/* SIZE 0x18 */
typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;

void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int kind, int id, int a3, Msg* a, Msg* b);
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x0049a880 */
int __cdecl fcn_0049a880(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Slot slots[4];
	Msg m2;
	Msg m1;
	Counts cnt;
	int idx;
	int r;
	int who;

	who = kind != 0 ? kind : 0x1e;
	if (busy == 0) {
		memset(slots, 0, sizeof slots);
		slots[0].id = 0x168;
		slots[1].id = 0x16c;
		slots[2].id = 0x297;
		slots[3].id = 0x2b7;
		fcn_004a51d0(e, 4, slots, &cnt);
		if (!(cnt.total == 6 && cnt.free == 0) && cnt.blocked != 4) {
			if (cnt.total >= 6 || cnt.free != 0) {
				if (cnt.free != 0) {
					idx = gm_RandomMod(4) & 0xffff;
					while (slots[idx].a < 1) {
						idx = (idx + 1) % 4;
					}
					m1.type = 1;
					m1.b = 1;
					m1.a = slots[idx].b;
					*out1 = m1;
					m2.type = 0;
					m2.a = -1;
					m2.b = -1;
					m2.d = 0x1e;
					*out2 = m2;
					return 0x1e;
				}
			} else {
				idx = gm_RandomMod(4) & 0xffff;
				while (slots[idx].a != 0) {
					idx = (idx + 1) % 4;
				}
				m1.type = 2;
				m1.b = 1;
				m1.a = slots[idx].id;
				m1.f = 0.05f;
				m2.type = 7;
				m2.a = *(int*) (e + 4);
				m2.b = 1;
				r = fcn_00495400(who, *(unsigned short*) e, 2, &m1, &m2);
				if (r != 0) {
					*out1 = m1;
					*out2 = m2;
					return r;
				}
			}
		}
	}
	return 0;
}
