#include <math.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char* g_entity_ptr;
extern char* g_773da8;
extern char g_7f4ca4[];
extern char g_677640[];

typedef struct Ff01c0Slot {
	int id;
	float dist;
	int type;
	float strength;
} Ff01c0Slot;

typedef struct Ff01c0Out {
	int h0;
	int h1;
	Ff01c0Slot slot[3];
} Ff01c0Out;

typedef struct Ff01c0Vec {
	float x;
	float y;
	float z;
} Ff01c0Vec;

int __cdecl fcn_00455350(char* src, char* pos, float* out);
void __cdecl fcn_00414ab0(float* a, float* b, char* ent);
int __cdecl fcn_00418000(int a1, float* pos, int n, float a4, float a5,
                         float a6, float a7, float a8, float a9, float* a10,
                         int a11, int a12, int a13);
int __cdecl fcn_004185a0(int a1, float* pos, int n, float a4, float a5,
                         float a6, float a7, float a8, float a9, float a10,
                         float a11, int a12);
int* __cdecl fcn_00417d00(int a1, float* pos, int n, float a4, float a5,
                          float a6, float a7, float a8);
int __cdecl fcn_00422460(int a1, char* name);
void __cdecl fcn_004193f0(int a1, int a2, int a3, float a4);
int __cdecl gm_ResolveEntityById(char** out, int a, int b, int c);
int __cdecl _ftol(float v);
void __cdecl fcn_004c4510(char* a1, int a2);
void __cdecl fcn_004c4670(int a1, int a2, int a3, void* a4);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5530(char* msg);

/* ADDRESS: GOLDTL 0x004f01c0 */
void __cdecl fcn_004f01c0(int a0, int a1, int a2, Ff01c0Out* a3)
{
	Ff01c0Out out;
	Ff01c0Vec pv;
	Ff01c0Vec va;
	Ff01c0Vec vb;
	Ff01c0Vec ov;
	char* in;
	char* rec;
	char* best;
	char* p;
	float cx;
	float cy;
	float cz;
	float xlo;
	float xhi;
	float ylo;
	float yhi;
	float zlo;
	float zhi;
	float dist;
	float bestdist;
	float rr;
	float s1;
	float s2;
	float scale;
	float tmp;
	float f1;
	float f2;
	float f3;
	int count;
	int off;
	int type;
	int k;
	int i;
	char neg;
	char msg[0xf4];

	in = (char*) a2;
	out.h1 = a1;
	for (i = 0; i < 3; i++) {
		out.slot[i].id = -1;
		out.slot[i].dist = 1000000.0f;
		out.slot[i].type = 0;
		out.slot[i].strength = 0.0f;
	}
	cx = *(float*) (in + 0x30);
	cy = *(float*) (in + 0x34);
	cz = *(float*) (in + 0x38);
	best = 0;
	bestdist = 100000.0f;
	count = 0;
	for (off = 0; off < 0xa900; off += 0xa9) {
		rec = (char*) g_entity_ptr + off;
		type = 0;
		rr = *(float*) (in + 0x58) * *(float*) 0x662a3c;
		if (*(int*) (rec + 1) == -1) {
			continue;
		}
		if (*(char*) rec == 0) {
			continue;
		}
		if (*(int*) (rec + 0x61) == 0) {
			continue;
		}
		fcn_00455350(*(char**) (rec + 0x61), *(char**) (rec + 0x61) + 0x4c,
		             &pv.x);
		dist = (float) sqrt((cx - pv.x) * (cx - pv.x) +
		                    (cy - pv.y) * (cy - pv.y) +
		                    (cz - pv.z) * (cz - pv.z));
		if (best == 0 || dist < bestdist) {
			bestdist = dist;
			best = rec;
		}
		s1 = *(float*) 0x6628a0 /
		     (dist * *(float*) 0x664138 + *(float*) 0x6628a0);
		s2 = *(float*) 0x6628a0 /
		     ((dist * *(float*) 0x662b30 + *(float*) 0x664138) * dist +
		      *(float*) 0x6628a0);
		fcn_00414ab0(&va.x, &vb.x, *(char**) (rec + 0x61));
		vb.x = (vb.x - va.x) * *(float*) 0x6628cc;
		vb.y = (vb.y - va.y) * *(float*) 0x6628cc;
		vb.z = (vb.z - va.z) * *(float*) 0x6628cc;
		xlo = pv.x - vb.x;
		xhi = pv.x + vb.x;
		ylo = pv.y - vb.y;
		yhi = pv.y + vb.y;
		zlo = pv.z - vb.z;
		zhi = pv.z + vb.z;
		if (cx < xlo || cx > xhi || cy < ylo || cy > yhi || cz < zlo ||
		    cz > zhi) {
			rr += rr;
			if (rr + cx < xlo || cx - rr > xhi || rr + cy < ylo ||
			    cy - rr > yhi || rr + cz < zlo || cz - rr > zhi) {
				continue;
			}
			type = 2;
			scale = s2;
		} else {
			type = 1;
			scale = s1;
		}
		scale = scale * *(float*) (in + 0x58);
		if (!(scale > *(float*) 0x662cf8)) {
			continue;
		}
		count = count + 1;
		tmp = scale * *(float*) 0x662910;
		if (!(tmp < *(float*) 0x662cf8)) {
			tmp = *(float*) 0x662cf8;
		}
		best = rec;
		k = -1;
		for (i = 0; i < 3; i++) {
			if (out.slot[i].id == -1) {
				k = i;
				break;
			}
		}
		if (k >= 0) {
			out.slot[k].dist = tmp;
			out.slot[k].id = *(int*) (rec + 1);
			out.slot[k].type = type;
			out.slot[k].strength = dist;
		} else {
			for (i = 0; i < 3; i++) {
				if (out.slot[i].dist < tmp &&
				    (k == -1 || out.slot[i].dist < out.slot[k].dist)) {
					k = i;
				}
			}
			if (k != -1) {
				out.slot[k].dist = tmp;
				out.slot[k].id = *(int*) (rec + 1);
				out.slot[k].type = type;
				out.slot[k].strength = dist;
			}
		}
	}
	rr = *(float*) (in + 0x58) * *(float*) 0x662a3c;
	f1 = *(float*) (in + 0x4c);
	xhi = f1 * *(float*) (in + 0x40);
	zhi = f1 * *(float*) (in + 0x48);
	yhi = 0.0f;
	cy = cy + *(float*) 0x6640cc;
	fcn_00418000(0, &cx, 200, 25.0f, 70.0f,
	             rr * *(float*) 0x6628bc, 900.0f, 100.0f, 70.0f, &xhi,
	             0x5dc, 7, 0x7fc0c0c0);
	if (fcn_004185a0(0, &ov.x, 100, 5.0f, 2.5f, 1.0f, 3.0f, -6.0f, 4.0f,
	                 7.0f, 8.0f, 0x7fc0c0c0) != 0) {
		f1 = rr * *(float*) 0x6652c8;
		f2 = rr * *(float*) 0x662d34;
		f3 = rr * *(float*) 0x6629d0;
	} else {
		f1 = rr * *(float*) 0x662910;
		f2 = rr * *(float*) 0x66414c;
		f3 = rr * *(float*) 0x662a3c;
	}
	fcn_00417d00(0, &cx, 0x96, f3, f2, f1, 20.0f, 200);
	p = (char*) fcn_00422460(0, g_677640);
	if (p != 0) {
		fcn_004193f0((int) p, *(int*) (best + 0x61), 0x6b, 15232.0f);
	}
	if (a0) {
		for (i = 0; i < 3; i++) {
			if (out.slot[i].id == -1) {
				continue;
			}
			p = 0;
			gm_ResolveEntityById(&p, 0, 0, out.slot[i].id);
			if (p == 0) {
				continue;
			}
			if (out.slot[i].type == 1) {
				msg[4] = 0x4f;
				if (*(unsigned short*) (p + 0x27) == 0xffff) {
					*(int*) (msg + 8) = *(int*) (g_773da8 + 4);
				} else {
					*(int*) (msg + 8) =
					    *(int*) (g_7f4ca4 +
					             (*(unsigned short*) (p + 0x27) &
					              0xffff) * 0x21c);
				}
				*(int*) (msg + 0xc) = *(int*) (p + 1);
				*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
				*(int*) (msg + 0x2c) = g_7f4c04;
				*(int*) (msg + 0x30) = g_7f4c08;
				*(short*) (msg + 0x34) = g_7f4c0c;
				msg[0x36] = 2;
				*(int*) (msg + 0x58) = *(int*) (p + 1);
				*(int*) (msg + 0x5c) =
				    _ftol(out.slot[i].strength);
				msg[0xb0] = 1;
				fcn_004c5530(msg);
			} else if (out.slot[i].type == 2) {
				neg = (char) _ftol(-out.slot[i].strength);
				fcn_004c4510(p, *(int*) (p + 1));
				fcn_004c4670(1, 1, 0x5c, &neg);
				fcn_004c5360();
			}
		}
	}
	if (a3 != 0) {
		*a3 = out;
	}
}
