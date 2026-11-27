/* GOLD twin of GOLDTL fcn_00455140: the parent link sits at 0x1f8, not 0x1fc. */
/* The per-parent temporary is a 16-byte vector; with a 12-byte one or a float
 * array c2 keeps all three results on the x87 stack and drops the frame. */

typedef struct D3_XFORM_NODE {
	char pad0[0x18c];
	float m[3][4];
	char pad1bc[0x1f8 - 0x1bc];
	struct D3_XFORM_NODE* parent;
} D3_XFORM_NODE;
/* SIZE 0x1fc */

typedef struct D3_DIR_XFORM_NODE {
	char pad0[0x18c];
	float m[3][4];
	char pad1bc[0x1fc - 0x1bc];
	struct D3_DIR_XFORM_NODE* parent;
} D3_DIR_XFORM_NODE;
/* SIZE 0x200 */

typedef struct D3_XFORM_VEC4 {
	float x;
	float y;
	float z;
	float w;
} D3_XFORM_VEC4;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00458800 */
void __cdecl d3_TransformDirection(D3_XFORM_NODE* n, float* in, float* out)
{
	D3_XFORM_NODE* p;
	D3_XFORM_VEC4 t;

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
#else
/* ADDRESS: GOLDTL 0x00455140 */
void __cdecl d3_TransformDirection(D3_DIR_XFORM_NODE* node, float* in, float* out)
{
	D3_DIR_XFORM_NODE* p;
	D3_XFORM_VEC4 t;

	p = node->parent;
	out[0] = node->m[1][0] * in[1] + node->m[0][0] * in[0] + node->m[2][0] * in[2];
	out[1] = node->m[1][1] * in[1] + node->m[0][1] * in[0] + node->m[2][1] * in[2];
	out[2] = node->m[1][2] * in[1] + node->m[0][2] * in[0] + node->m[2][2] * in[2];
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
#endif
