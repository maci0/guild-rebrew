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

typedef struct UseObjectQuery {
	char* e;
	int a;
	int b;
	int c;
	int d;
} UseObjectQuery;

extern float g_1009638;
extern float g_1009658;
char* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_005c61e0(int);
int __cdecl fcn_005dbf10(char* ctx, UseObjectQuery* q);

/* Method 0x1d (UseObject) start callback: looks up the target object record and its
 * type entry, queries it, and stores the resulting speed (+/-) in the shared float. */
/* ADDRESS: GOLDTL 0x0049a7b0 */
int __cdecl fcn_0049a7b0(char* ctx, int* arg)
{
	char* e;
	char* rec;
	int r;
	float t;
	UseObjectQuery q;

	e = fcn_00502cd0(*(int*) (ctx + 0x178), 1, 1, arg[1]);
	r = 0;
	if (!e)
		return r;
	rec = (char*) fcn_005c61e0(*(unsigned short*) e);
	if (rec) {
		q.e = e;
		q.a = -1;
		q.b = -1;
		q.c = 0;
		q.d = 0;
		if (fcn_005dbf10(ctx, &q) == 1) {
			if (q.c == 1) {
				g_1009658 = g_1009638 * *(float*) (rec + 0xc);
				return 0x1d;
			}
			if (q.c == -1) {
				t = g_1009638 * *(float*) (rec + 0xc);
				g_1009658 = -(t * *(float*) 0x6628cc);
			}
			return 0x1d;
		}
	}
	return 0;
}

/* ADDRESS: GOLDTL 0x0049a880 */
int __cdecl fcn_0049a880(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Slot slots[4];
	Msg m2;
	Msg m1;
	Counts cnt;
	int idx;
	int result;
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
				result = fcn_00495400(who, *(unsigned short*) e, 2, &m1, &m2);
				if (result != 0) {
					*out1 = m1;
					*out2 = m2;
				}
				return result;
			}
		}
	}
	return 0;
}
