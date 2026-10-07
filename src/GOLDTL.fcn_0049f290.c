// FUNCTION: GOLDTL 0x0049f290

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

extern Rec* g_90e094;
extern int g_6643d8[];
extern int g_7f4ca4[];

unsigned short __cdecl fcn_0042e410(int n);
float __cdecl gm_RandomFloat01(void);
char* __cdecl fcn_00502cd0(int id, int a, int b, int c, int d);
unsigned short* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);

int __cdecl fcn_0049f290(int busy, unsigned short* self, int pending, Act* out)
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

	step = g_6643d8[fcn_0042e410(0x10)];
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
	idx = fcn_0042e410(n);
	while (count < 4 && n != 0) {
		e = &g_90e094[idx];
		if (e->type == 0x37 && e->owner != 0xffff && e->owner != *self) {
			r = fcn_00502cd0(e->x5d, 2, 6, 0, 0x12d);
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
			o = fcn_00508e40(*p);
			if (o != 0 && o != self) {
				cnt++;
				sum += fcn_0050f980(*self, *o, 1);
			}
			p++;
		}
		if (cnt == 0 && fcn_0042e410(4) == 0) {
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
	idx = fcn_0042e410(count);
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
		out->a = g_7f4ca4[cand[sel]->owner * 135];
		out->b = 0;
		return 0x35;
	}
noop:
	out->code = 0;
	out->a = -1;
	out->b = 0x6e6f6f70;
	return 0x35;
}
