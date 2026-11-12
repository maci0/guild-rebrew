#include <stdlib.h>
extern unsigned char g_14cbc60, g_14cbc68; extern float* g_14cbc64;
extern short g_14cbc72, g_678c20[8]; extern unsigned short g_14cbc7c, g_14cbc7e;
extern float g_14cbc80; extern int g_678c08, g_678c0c;

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
	unsigned short cursor;
	float score;
	int idx;
	p = &grid->nodes[node];
	h = p->f16;
	p->flags = (unsigned char) ((p->flags & 0xfe) | 2);
	if (h != 0xffff) {
		grid->nodes[h].f18 = p->f18;
	}
	for (i = 0; i < 8; i++) {
		t = g_678c20[i & 7];
		t += ((short*) 0x678c10)[i & 7];
		idx = (node + t) & 0xffff;
		q = &grid->nodes[idx];
		if (q->mark == g_14cbc72 && (q->flags & g_14cbc68) != 0) {
			q->flags = (unsigned char) (q->flags | g_14cbc60);
			p->flags = (unsigned char) (p->flags | g_14cbc68);
			g_14cbc7e = (unsigned short) idx;
			return node;
		}
		costs = g_14cbc64;
		ng = *(float*) (0x678c30 + i * 4) * costs[q->type] + p->g;
		if (costs[q->type] >= *(double*) 0x662950) {
			if (q->mark == g_14cbc72) {
				if (!(ng < q->g)) {
					continue;
				}
				if (q->mark == g_14cbc72 && (q->flags & 1) != 0) {
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
				dist = abs((int) ((unsigned int)g_14cbc7c >> (g_678c0c & 0xffff)) - ((unsigned int)idx >> (g_678c0c & 0xffff)));
				dist += abs((int) (g_14cbc7c & g_678c08) - (idx & g_678c08));
				x = (float) dist * g_14cbc80;
			}
			q->parent = node;
			score = x + ng;
			q->f = score;
			q->g = ng;
			q->h = x;
			if (q->mark != g_14cbc72 || (q->flags & 2) == 0) {
				q->mark = g_14cbc72;
				q->flags = (unsigned char) (q->flags & 0xfd);
				q->flags = (unsigned char) ((q->flags & ~g_14cbc68) | 1);
				q->flags = (unsigned char) (q->flags | g_14cbc60);
				if (h == 0xffff) {
					q->f18 = 0xffff;
					q->f16 = 0xffff;
					h = (unsigned short) idx;
				} else {
					cursor = h;
					r = &grid->nodes[cursor];
					while (r->f16 != 0xffff) {
						if (score < r->f) {
							q->f16 = cursor;
							q->f18 = r->f18;
							if (r->f18 != 0xffff)
								grid->nodes[r->f18].f16 = (unsigned short) idx;
							else
								h = (unsigned short) idx;
							r->f18 = (unsigned short) idx;
							break;
						}
						cursor = r->f16;
						r = &grid->nodes[cursor];
					}
					if (r->f16 == 0xffff) {
						q->f18 = cursor;
						q->f16 = 0xffff;
						grid->nodes[cursor].f16 = (unsigned short) idx;
					}
				}
			}
			if (idx == g_14cbc7c) {
				return h;
			}
		}
	}
	return h;
}
