typedef struct Node Node;

// SIZE 0x200
struct Node {
	char p0[0x4c];
	float off[3];
	char p58[0x14];
	float pivot[3];
	float pos[3];
	char p84[0x108];
	float m[4][4];
	char p1cc[0x30];
	Node* parent;
};

// FUNCTION: GOLDTL 0x00455350

void __cdecl fcn_00455350(Node* n, float* in, float* out)
{
	float x;
	float y;
	float z;

	out[0] = n->pos[0] + in[0];
	out[1] = n->pos[1] + in[1];
	out[2] = n->pos[2] + in[2];
	n = n->parent;
	while (n != 0) {
		x = n->pivot[0] + out[0];
		y = n->pivot[1] + out[1];
		z = n->pivot[2] + out[2];
		out[0] = z * n->m[2][0] + y * n->m[1][0] + x * n->m[0][0];
		out[1] = z * n->m[2][1] + y * n->m[1][1] + x * n->m[0][1];
		out[2] = z * n->m[2][2] + y * n->m[1][2] + x * n->m[0][2];
		out[0] -= n->pivot[0];
		out[1] -= n->pivot[1];
		out[2] -= n->pivot[2];
		out[0] += n->off[0];
		out[1] += n->off[1];
		out[2] += n->off[2];
		out[0] += n->pos[0];
		out[1] += n->pos[1];
		out[2] += n->pos[2];
		n = n->parent;
	}
}
