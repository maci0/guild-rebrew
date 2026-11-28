

#pragma pack(1)
typedef struct Rec {
	unsigned char type;
	int id;
	char pad5[0x22];
	unsigned short owner;
	char pad29[0x34];
	int x5d;
	char pad61[0x48];
} Rec;
// SIZE 0xa9
#pragma pack()

typedef struct Act {
	unsigned char code;
	char pad[3];
	int a;
	int b;
} Act;
// SIZE 0xc

extern unsigned char* lpGebaeudeINST;
extern int g_6643d8[];
extern int gm_EntityIdField[];

unsigned short __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01(void);
char* __cdecl gm_QueryEntities(int id, int a, int b, int c, int d);
unsigned short* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDDE 0x0048dcc0 */
int __cdecl ai_StartStammtisch(int busy, unsigned short* self, int pending, Act* out)
{
	int sel;
	int step;
	Rec* cand[4];
	char* res[4];
	int flag[4];
	int n;
	int idx;
	int count;
	int i;
	int k;
	int* p;
	int cnt;
	float sum;
	unsigned short* o;
	Rec* e;
	char* r;

	step = g_6643d8[gm_RandomMod(0x10)];
	sel = -1;
	if ((*(int*) ((char*) self + 0x1c8) & 0x2000000) != 0) {
		return 0;
	}
	if (busy != 0) {
		return 0;
	}
	if (pending != 0) {
		return 0;
	}
	n = 0x100;
	count = 0;
	idx = gm_RandomMod(n);
	while (count < 4 && n != 0) {
		e = (Rec*) (lpGebaeudeINST + idx * sizeof(Rec));
		if (e->type == 0x37 && e->owner != 0xffff && e->owner != *self) {
			r = gm_QueryEntities(e->x5d, 2, 6, 0, 0x12d);
			if (r != 0) {
				cand[count] = e;
				res[count] = r;
				count++;
			}
		}
		n--;
		idx = (idx + step) % 256;
	}
	if (count == 0) {
		if (gm_RandomFloat01() > 0.33f) {
			goto noop;
		}
		return 0;
	}
	for (i = 0; i < count; i++) {
		flag[i] = 0;
		p = (int*) (res[i] + 0x1c);
		for (k = 4; k != 0; k--) {
			flag[i] |= *p == -1;
			if (sel == -1) {
				sel = *p == *(int*) (self + 2) ? i : -1;
			}
			p++;
		}
	}
	if (sel != -1) {
		sum = 0.0f;
		cnt = 0;
		p = (int*) (res[sel] + 0x1c);
		for (k = 4; k != 0; k--) {
			o = gm_LookupEntityRecordById(*p);
			if (o != 0 && o != self) {
				cnt++;
				sum += gm_CalcEntityFavor(*self, *o, 1);
			}
			p++;
		}
		if (cnt == 0 && gm_RandomMod(4) == 0) {
			out->code = 4;
			out->a = cand[sel]->id;
			out->b = 0x6c656176;
			return 0x35;
		}
		sum = sum / (float) (cnt * 100);
		if (sum > 0.666f) {
			if (gm_RandomFloat01() + 0.166667f < sum) {
				out->code = 4;
				out->b = 0x6c656176;
				out->a = cand[sel]->id;
				return 0x35;
			}
			goto noop;
		}
		return 0;
	}
	idx = gm_RandomMod(count);
	sel = -1;
	for (k = 0; k < count; k++) {
		if (flag[idx] == 1) {
			sel = idx;
			break;
		}
		idx = (idx + 1) % count;
	}
	if (sel == -1) {
		return 0;
	}
	if (gm_RandomFloat01() > 0.75f) {
		out->code = 4;
		out->a = cand[sel]->id;
		out->b = 0x6a6f696e;
		out->code = 0x12;
		out->a = gm_EntityIdField[cand[sel]->owner * 135];
		out->b = 0;
		return 0x35;
	}
noop:
	out->code = 0;
	out->a = -1;
	out->b = 0x6e6f6f70;
	return 0x35;
}
