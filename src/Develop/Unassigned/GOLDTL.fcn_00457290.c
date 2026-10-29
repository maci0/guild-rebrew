typedef struct Item0457290 Item0457290;
typedef struct Master0457290 Master0457290;
typedef struct Node0457290 Node0457290;
typedef struct Sub0457290 Sub0457290;
typedef struct Ent0457290 Ent0457290;
typedef struct Tex0457290 Tex0457290;

/* SIZE 0x70 */
struct Tex0457290 {
	char name[0x50];
	int f50;
};

struct Ent0457290 {
	char pad000[0x1d8];
	int f1d8;
};

/* SIZE 0x4a4 */
struct Sub0457290 {
	char pad000[0x318];
	Ent0457290* p318;
	char pad31c[0x4a0 - 0x31c];
	unsigned char f4a0;
};

/* SIZE 0x9c */
struct Item0457290 {
	Tex0457290* f0;
	int f4;
	char* f8;
	char* fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	char pad28[0x70 - 0x28];
	int f70;
	int f74;
	int f78;
	int f7c;
	char pad80[0x98 - 0x80];
	unsigned char f98;
	char pad99[0x9c - 0x99];
};

struct Master0457290 {
	char pad000[0x11f0];
	int f11f0;
	int f11f4;
	char pad11f8[0x1384 - 0x11f8];
	Item0457290 items[4];
};

/* SIZE 0x21c */
struct Node0457290 {
	char pad000[0x94];
	float f94;
	char pad098[0x1cc - 0x98];
	Sub0457290* p1cc;
	char pad1d0[0x1ec - 0x1d0];
	Master0457290* p1ec;
	char pad1f0[0x215 - 0x1f0];
	unsigned char f215;
	char pad216[2];
	int f218;
};

typedef struct Col0457290 {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col0457290;

Tex0457290* __cdecl fcn_0045c5b0(char* name, Col0457290 c, unsigned int flags,
                                 unsigned int flags2);
void __cdecl fcn_0045ce90(Tex0457290* t);
void __cdecl fcn_00455350(char* object, float* in, float* out);
void __cdecl fcn_00455140(char* node, float* in, float* out);
int __cdecl fcn_00451840(float* a, float* b, float eps);
int __cdecl fcn_00456630(void* obj, char b, unsigned int key,
                         unsigned int stamp, int unused);
int __cdecl fcn_004582d0(char* a0, char* p2, char* p1, char* a2, float* va,
                         float* vb, char* a1, Item0457290* rec, char* a3);
int __cdecl fcn_00457630(Item0457290* rec, unsigned int map);

#include <string.h>

/* ADDRESS: GOLDTL 0x00457290 */
char __cdecl fcn_00457290(Node0457290* a0, Node0457290* a1, char* a2, char* a3)
{
	Master0457290* m;
	Item0457290* rec;
	Sub0457290* q;
	float tol;
	char* p1;
	char* p2;
	float va[4];
	float vb[4];
	float vc[4];
	unsigned char b;
	int i;
	int r;

	rec = 0;
	if (*(int*) 0x104061c != 0
	    && a0->f218 < 5
	    && (a0->f215 & 1) != 0
	    && a0->p1ec != 0
	    && (a1->f215 & 1) != 0
	    && a1->f94 != *(double*) 0x662950) {
		m = a0->p1ec;
		i = 0;
		do {
			if (m->items[i].f0 != 0 && m->items[i].f8 == (char*) a1) {
				rec = &m->items[i];
				break;
			}
		} while (++i < 4);
		if (i == 4) {
			i = 0;
			do {
				if (m->items[i].f0 == 0) {
					goto alloc;
				}
			} while (++i < 4);
			return 0;
alloc:
			rec = &m->items[i];
			rec->f8 = (char*) a1;
			rec->f10 = 0;
			rec->f14 = 0;
			rec->f18 = 0;
			rec->f70 = -1;
			b = (unsigned char) ((a0->f215 >> 1) & 1);
			rec->f1c = 0;
			rec->f98 = b;
			rec->f20 = 0;
			rec->f24 = 0;
			if (b != 0) {
				Col0457290 c;
				Tex0457290* t;

				memset(&c, 0, sizeof(c));
				c.a = 0x7f;
				c.c1 = 1;
				t = fcn_0045c5b0((char*) 0x67bcb8, c, 0, 0);
				rec->f0 = t;
				if (t != 0 && t->f50 == 0) {
					fcn_0045ce90(t);
				}
			} else {
				Ent0457290* e;
				unsigned int lim;
				unsigned int off;
				float v;

				q = a0->p1cc;
				lim = *(unsigned int*) 0x104061c;
				e = q->p318;
				if (e != 0 && *(char*) 0x10405f8 != 0) {
					v = *(float*) ((char*) e + 0x1d8);
					off = 0;
					do {
						if (v < *(float*) (0x662da0 + off)) {
							break;
						}
						off += 4;
						lim += lim;
					} while (off < 8);
					if (lim >= *(unsigned int*) 0x10405fc) {
						lim = *(unsigned int*) 0x10405fc;
					}
				}
				rec->f0 = (Tex0457290*) fcn_00456630(rec,
				    *(char*) 0x1040601, lim, *(unsigned int*) 0x6b8008,
				    (int) &rec->fc);
			}
		}
		if (rec == 0) {
			goto end;
		}
		if (rec->f0 == 0) {
			goto end;
		}
		if (rec->f0->f50 == 0) {
			goto end;
		}
		if (rec->fc != 0) {
			*(int*) (rec->fc + 8) = *(int*) 0x6b8008;
		}
		m = a0->p1ec;
		q = a0->p1cc;
		p1 = (char*) q;
		p2 = (char*) q;
		if (m->f11f4 > 0 && m->f11f0 > 0) {
			p1 = (char*) m + 0xee0;
		}
		fcn_00455350((char*) a1, (float*) ((char*) a1 + 0x4c), vb);
		if ((a1->f215 & 4) != 0) {
			tol = 0.01f;
			fcn_00455140((char*) a1, (float*) 0x662d40, va);
		} else {
			tol = 1.0f;
			fcn_00455350((char*) a0, (float*) ((char*) a0 + 0x4c), vc);
			va[0] = vc[0] - vb[0];
			va[1] = vc[1] - vb[1];
			va[2] = vc[2] - vb[2];
		}
		r = fcn_00451840(va, (float*) &rec->f1c, tol);
		b = (r != 0 && q->f4a0 == 0) ? 0 : 1;
		if (a2 != 0) {
			unsigned char mx;
			unsigned char cv;
			unsigned char* cp;
			int x;
			int y;

			if (b != 0) {
				goto submit;
			}
			if (rec->f70 == -1) {
				goto end;
			}
			if (rec->f98 != 0) {
				goto end;
			}
			mx = 0;
			for (y = rec->f70; y <= rec->f78; y++) {
				for (x = rec->f74; x <= rec->f7c; x++) {
					cv = *(unsigned char*) (a2 + 0x28e + (y * 8 + x) * 500);
					if (mx <= cv) {
						mx = cv;
					}
				}
			}
			if (mx == 0) {
				goto end;
			}
			if (mx == rec->f18) {
				goto end;
			}
		} else {
			if (b == 0) {
				goto end;
			}
		}
submit:
		fcn_004582d0((char*) a0, p2, p1, a2, va, vb, (char*) a1, rec, a3);
		fcn_00457630(rec, *(unsigned int*) 0x6b8300);
	}
end:
	return 0;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_00457290[16] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
