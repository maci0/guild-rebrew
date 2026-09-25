// FUNCTION: GOLD 0x458800
// SIZE: 247
/* GOLD twin of GOLDTL fcn_00455140: the parent link sits at 0x1f8, not 0x1fc. */
// The per-parent temporary is a 16-byte vector; with a 12-byte one or a float
// array c2 keeps all three results on the x87 stack and drops the frame.

typedef struct Node0458800 {
	char pad0[0x18c];
	float m[3][4];
	char pad1bc[0x1f8 - 0x1bc];
	struct Node0458800* parent;
} Node0458800;
// SIZE 0x1fc

typedef struct V4_0458800 {
	float x;
	float y;
	float z;
	float w;
} V4_0458800;

void __cdecl fcn_00458800(Node0458800* n, float* in, float* out)
{
	Node0458800* p;
	V4_0458800 t;

	p = n->parent;
	out[0] = n->m[1][0] * in[1] + n->m[0][0] * in[0] + n->m[2][0] * in[2];
	out[1] = n->m[1][1] * in[1] + n->m[0][1] * in[0] + n->m[2][1] * in[2];
	out[2] = n->m[1][2] * in[1] + n->m[0][2] * in[0] + n->m[2][2] * in[2];
	while (p != 0) {
		t.x = p->m[0][0] * out[0] + p->m[2][0] * out[2] + p->m[1][0] * out[1];
		t.y = p->m[0][1] * out[0] + p->m[2][1] * out[2] + p->m[1][1] * out[1];
		t.z = p->m[0][2] * out[0] + p->m[2][2] * out[2] + p->m[1][2] * out[1];
		out[0] = t.x;
		out[1] = t.y;
		out[2] = t.z;
		p = p->parent;
	}
}
