

// SIZE 0x18
typedef struct {
	unsigned char valid;
	char pad1[3];
	int v[5];
} Pos;

// SIZE 0x21c
typedef struct {
	char pad0[0x132];
	unsigned char kind;
	char pad133[0xe5];
	unsigned char flags;
	char pad219[3];
} Actor;

typedef struct Plan Plan;

// SIZE 0x94
struct Plan {
	unsigned char kind;
	char pad1[0x23];
	void (__cdecl *rate)(float *, float *, int, Actor *, int, Pos *, Pos *);
	int (__cdecl *pick)(int, Actor *, int, Pos *, Pos *);
	char pad2c[0x68];
};

extern char g_7f4ca0[];
extern char g_1008540[];

int __cdecl fcn_00495150(int);
void __cdecl fcn_00495120(int);
void __cdecl fcn_00495140(void);

int __cdecl fcn_00495400(int who, int idx, int arg, Pos *out1, Pos *out2)
{
	float best1;
	float best2;
	float s1;
	float s2;
	int i;
	int res2;
	int res1;
	Pos p1;
	Pos p2;
	Pos a1;
	Pos a2;
	Pos b1;
	Pos b2;
	Actor *me;
	Plan *pl;
	int r;

	best1 = -1e30f;
	best2 = -1e30f;
	res1 = 0;
	res2 = 0;
	a1.valid = 0;
	b1.valid = 0;
	me = &((Actor*)g_7f4ca0)[idx];
	a2.valid = 0;
	b2.valid = 0;
	if (fcn_00495150(who) != 0) {
		return 0;
	}
	if (me->flags == 0) {
		me->flags = 1;
	}
	for (i = 0; i < 73; i++) {
		pl = &((Plan*)g_1008540)[i];
		if (pl->kind == 0 || pl->kind == me->kind || fcn_00495150(pl->kind) != 0) {
			continue;
		}
		fcn_00495120(pl->kind);
		p1 = *out1;
		p2 = *out2;
		if (pl->rate != 0) {
			pl->rate(&s1, &s2, i, me, arg, &p1, &p2);
		}
		if (s1 >= best1 || s2 >= best2) {
			if (pl->pick != 0) {
				r = pl->pick(who, me, arg, &p1, &p2);
				if (r != 0) {
					if (s1 >= best1) {
						best1 = s1;
						res1 = r;
						a1 = p1;
						a2 = p2;
					}
					if (s2 >= best2) {
						best2 = s2;
						res2 = r;
						b1 = p1;
						b2 = p2;
					}
				}
			}
		}
		fcn_00495140();
	}
	if (best1 != 0.0f && best1 >= best2) {
		*out1 = a1;
		*out2 = a2;
		return res1;
	}
	*out1 = b1;
	*out2 = b2;
	return res2;
}
