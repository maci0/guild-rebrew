// FUNCTION: GOLDTL 0x455140
// The per-parent temporary is a 16-byte vector; with a 12-byte one or a float
// array c2 keeps all three results on the x87 stack and drops the frame.

typedef struct Node0455140 {
	char pad0[0x18c];
	float m[3][4];
	char pad1bc[0x1fc - 0x1bc];
	struct Node0455140* parent;
} Node0455140;
// SIZE 0x200

typedef struct V4_0455140 {
	float x;
	float y;
	float z;
	float w;
} V4_0455140;

void __cdecl fcn_00455140(Node0455140* n, float* in, float* out)
{
	Node0455140* p;
	V4_0455140 t;

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
