#include <stdlib.h>

/* SIZE 0x1c */
typedef struct PathNode {
	int type;
	short mark;
	short pad06;
	float f;
	float g;
	float h;
	unsigned char flags;
	unsigned char pad15;
	unsigned short f16;
	unsigned short f18;
	unsigned short parent;
} PathNode;

typedef struct PathGrid {
	char pad00[0x20];
	int width;
	PathNode* nodes;
} PathGrid;

/* ADDRESS: GOLDTL 0x00421ba0 */
unsigned short __cdecl fcn_00421ba0(PathGrid* grid, unsigned short node)
{
	PathNode* p;
	PathNode* q;
	PathNode* r;
	float* costs;
	int dist;
	float ng;
	float x;
	int i;
	unsigned short t;
	unsigned short h;
	int idx;

	p = &grid->nodes[node];
	h = p->f16;
	p->flags = (unsigned char) ((p->flags & 0xfe) | 2);
	if (h != 0xffff) {
		grid->nodes[h].f18 = p->f18;
	}

	for (i = 0; i < 8; i++) {
		t = ((short*) 0x678c20)[i & 7];
		t += ((short*) 0x678c10)[i & 7];
		idx = (node + t) & 0xffff;
		q = &grid->nodes[idx];
		if (q->mark == *(short*) 0x14cbc72 && (q->flags & *(unsigned char*) 0x14cbc68) != 0) {
			q->flags = (unsigned char) (q->flags | *(unsigned char*) 0x14cbc60);
			p->flags = (unsigned char) (p->flags | *(unsigned char*) 0x14cbc68);
			*(unsigned short*) 0x14cbc7e = (unsigned short) idx;
			return node;
		}
		costs = *(float**) 0x14cbc64;
		ng = *(float*) (0x678c30 + i * 4) * costs[q->type] + p->g;
		if (costs[q->type] >= *(double*) 0x662950) {
			if (q->mark == *(short*) 0x14cbc72) {
				if (!(ng < q->g)) {
					continue;
				}
				if (q->mark == *(short*) 0x14cbc72 && (q->flags & 1) != 0) {
					x = q->h;
					if (q->f18 != 0xffff) {
						grid->nodes[q->f18].f16 = q->f16;
					} else {
						h = q->f16;
					}
					if (q->f16 != 0xffff) {
						grid->nodes[q->f16].f18 = q->f18;
					}
				} else {
					goto calc;
				}
			} else {
calc:
				dist = abs((int) (*(unsigned short*) 0x14cbc7c >> (*(int*) 0x678c0c & 0xffff)) - (idx >> (*(int*) 0x678c0c & 0xffff)));
				dist += abs((int) (*(unsigned short*) 0x14cbc7c & *(int*) 0x678c08) - (idx & *(int*) 0x678c08));
				x = (float) dist * *(float*) 0x14cbc80;
			}
			q->parent = node;
			q->f = x + ng;
			q->g = ng;
			q->h = x;
			if (q->mark != *(short*) 0x14cbc72 || (q->flags & 2) == 0) {
				q->mark = *(short*) 0x14cbc72;
				q->flags = (unsigned char) (q->flags & 0xfd);
				q->flags = (unsigned char) ((q->flags & ~*(unsigned char*) 0x14cbc68) | 1);
				q->flags = (unsigned char) (q->flags | *(unsigned char*) 0x14cbc60);
				if (h == 0xffff) {
					q->f18 = 0xffff;
					q->f16 = 0xffff;
					h = (unsigned short) idx;
				} else {
					r = &grid->nodes[h];
					while (r->f16 != 0xffff) {
						if (x < r->f) {
							break;
						}
						h = r->f16;
						r = &grid->nodes[h];
					}
					q->f16 = h;
					q->f18 = r->f18;
					if (r->f18 != 0xffff) {
						grid->nodes[r->f18].f16 = (unsigned short) idx;
					} else {
						h = (unsigned short) idx;
					}
					r->f18 = (unsigned short) idx;
					if (r->f16 == 0xffff) {
						q->f18 = h;
						q->f16 = 0xffff;
						grid->nodes[h].f16 = (unsigned short) idx;
					}
				}
			}
			if (idx == *(unsigned short*) 0x14cbc7c) {
				return h;
			}
		}
	}
	return h;
}
