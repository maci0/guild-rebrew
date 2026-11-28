typedef struct Node Node;

/* SIZE 0x200 */
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

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00458a10 */
void __cdecl d3_TransformPoint(char* obj, const float* in, float* out)
{
    float x;
    float y;
    float z;

    out[0] = *(float*) (obj + 0x78) + in[0];
    out[1] = *(float*) (obj + 0x7c) + in[1];
    out[2] = *(float*) (obj + 0x80) + in[2];
    obj = *(char**) (obj + 0x1f8);
    while (obj != 0) {
        x = *(float*) (obj + 0x6c) + out[0];
        y = *(float*) (obj + 0x70) + out[1];
        z = *(float*) (obj + 0x74) + out[2];
        out[0] = z * *(float*) (obj + 0x1ac) + y * *(float*) (obj + 0x19c) + x * *(float*) (obj + 0x18c);
        out[1] = z * *(float*) (obj + 0x1b0) + y * *(float*) (obj + 0x1a0) + x * *(float*) (obj + 0x190);
        out[2] = z * *(float*) (obj + 0x1b4) + y * *(float*) (obj + 0x1a4) + x * *(float*) (obj + 0x194);
        out[0] -= *(float*) (obj + 0x6c);
        out[1] -= *(float*) (obj + 0x70);
        out[2] -= *(float*) (obj + 0x74);
        out[0] += *(float*) (obj + 0x4c);
        out[1] += *(float*) (obj + 0x50);
        out[2] += *(float*) (obj + 0x54);
        out[0] += *(float*) (obj + 0x78);
        out[1] += *(float*) (obj + 0x7c);
        out[2] += *(float*) (obj + 0x80);
        obj = *(char**) (obj + 0x1f8);
    }
}
#else
/* ADDRESS: GOLDTL 0x00455350 */
/* ADDRESS: GOLDDE 0x0044ac00 */
void __cdecl d3_TransformPoint(char* object, float* in, float* out)
{
	Node* n;
	float x;
	float y;
	float z;

	n = (Node*) object;
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
#endif
