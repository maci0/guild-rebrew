typedef struct Ent {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	unsigned char alive;
	char pad9[0x166 - 9];
	unsigned char x166;
	char pad167[2];
	unsigned char x169;
	char pad16a[0x1cc - 0x16a];
	int flags;
	char pad1d0[0x21c - 0x1d0];
} Ent;
// SIZE 0x21c

typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[3];
	int xc;
	char pad10[8];
} Rec18;
// SIZE 0x18

typedef struct Income {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	char pad3;
	int va;
	int vb;
	int vc;
} Income;
// SIZE 0x10

extern Ent g_7f4ca0[768];
extern float g_665264[];
extern int g_773d48;

int __cdecl fcn_004e8b40(int idx, Rec18* out);
int __cdecl fcn_004f4830(int idx, void* dst);
char* __cdecl fcn_0050e4a0(int n);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_004c6ae0(int, int);

// FUNCTION: GOLDTL 0x4fcda0
// SIZE: 681
int __cdecl fcn_004fcda0(unsigned short id, int pay, Income* out)
{
	Rec18 q;
	int info[9];
	float mult;
	char* w;
	int r;
	int c;
	int amount;

	r = 0;
	out->a = g_7f4ca0[id].x166;
	out->b = g_7f4ca0[id].x169;
	if (g_7f4ca0[id].flags & 0x1000) {
		c = 0x26;
	} else if (g_7f4ca0[id].flags & 0x2000) {
		c = 0x27;
	} else if (g_7f4ca0[id].flags & 0x800) {
		c = 0x25;
	} else if (g_7f4ca0[id].flags & 0x400) {
		c = 0x24;
	} else {
		c = (g_7f4ca0[id].flags & 0x200) ? 0x23 : 0;
	}
	out->c = c;
	out->va = 0;
	out->vb = 0;
	out->vc = 0;
	if (g_7f4ca0[id].id != 0xffff && g_7f4ca0[id].type < 0xa && g_7f4ca0[id].alive > 0
	    && (g_7f4ca0[id].x166 != 0 || g_7f4ca0[id].x169 != 0 || (g_7f4ca0[id].flags & 0xe00) != 0)) {
		fcn_004f4830(0xf, info);
		mult = g_665264[info[6]];
		fcn_004e8b40(g_7f4ca0[id].x169, &q);
		out->vb = (int) ((q.xc << 5) * mult);
		fcn_004e8b40(g_7f4ca0[id].x166, &q);
		out->va = (int) ((q.xc << 5) * mult);
		fcn_004e8b40(out->c, &q);
		out->vc = (int) ((q.xc << 5) * mult);
		r = 1;
		if (pay != 0) {
			w = fcn_0050e4a0(1);
			if (w == 0) {
				return 0;
			}
			if (fcn_00502cd0(*(int*) (w + 0x5d), 2, 6, 0, 0x115) == 0) {
				return 0;
			}
			if (out->va != 0) {
				fcn_004c51a0(g_7f4ca0[id].owner, -1, 0, out->va);
				g_773d48++;
			}
			if (out->vb != 0) {
				fcn_004c51a0(g_7f4ca0[id].owner, -1, 0, out->vb);
				g_773d48++;
			}
			if (out->vc != 0) {
				fcn_004c51a0(g_7f4ca0[id].owner, -1, 0, out->vc);
				g_773d48++;
			}
			if (g_7f4ca0[id].type == 3) {
				amount = (fcn_0042e410((unsigned short) (q.x8 + 2)) + q.x8) * 6400;
				fcn_004c51a0(g_7f4ca0[id].owner, -1, 0, amount);
				fcn_004c6ae0(g_7f4ca0[id].owner, q.x8);
				g_773d48 += 2;
			}
		}
	}
	return r;
}
