// FUNCTION: GOLDTL 0x4a6ea0
// SIZE: 167

// SIZE 0x34
typedef struct {
	int ids[5];
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int pad[3];
} Rec34;

// SIZE 0xc0
typedef struct {
	int f0;
	int f4;
	int f8;
	Rec34 recs[3];
	char tail[0x18];
} State;

// SIZE 0x10
typedef struct {
	int a;
	int b;
	int c;
	int d;
} Slot10;

extern Slot10 g_1007ce0[24];

int __cdecl fcn_0042e410(int id);

int __cdecl fcn_004a6ea0(State* s)
{
	int i;
	int j;

	if (s == 0) {
		return 0;
	}
	*((unsigned char*) s + 0xb4) = 0x18;
	*((unsigned char*) s + 0xb5) = 0;
	*(int*) ((char*) s + 0xa0) = 0;
	s->f0 = 0;
	*(int*) ((char*) s + 0xb0) = (unsigned short) fcn_0042e410(3);
	*(int*) ((char*) s + 0xbc) = 0;
	for (i = 0; i < 24; i++) {
		g_1007ce0[i].c = 3;
		g_1007ce0[i].d = 0;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			s->recs[i].ids[j] = -1;
		}
		s->recs[i].f14 = 0;
		s->recs[i].f24 = 0;
		s->recs[i].f1c = -1;
		s->recs[i].f18 = (unsigned short) fcn_0042e410(5) == 1;
		s->recs[i].f24 = 0;
		s->recs[i].f20 = -1;
	}
	return 1;
}
