typedef struct
{
	float m[4][4];
} D3_MAT4X4;
// SIZE 0x40

void __cdecl d3_BuildViewMatrix(char* a, int b, D3_MAT4X4* m, D3_MAT4X4* out);
D3_MAT4X4* __stdcall fcn_005eb970(D3_MAT4X4* out, D3_MAT4X4* a, D3_MAT4X4* b);

/* ADDRESS: GOLDTL 0x004557c0 */
/* ADDRESS: GOLDDE 0x0044af80 */
void __cdecl d3_ComposeObserverMatrix(char* node, char* observer, int flag, D3_MAT4X4* out)
{
	D3_MAT4X4 id;
	D3_MAT4X4 tmp;

	id.m[0][1] = id.m[0][2] = id.m[0][3] = id.m[1][0] = id.m[1][2] = id.m[1][3] = id.m[2][0] = id.m[2][1] = id.m[2][3] = id.m[3][0] = id.m[3][1] = id.m[3][2] = 0.0f;
	id.m[0][0] = id.m[1][1] = id.m[2][2] = id.m[3][3] = 1.0f;
	if (observer != 0) {
		d3_BuildViewMatrix(node, flag, &id, &tmp);
		tmp.m[3][0] -= *(float*) (observer + 0x4c);
		tmp.m[3][1] -= *(float*) (observer + 0x50);
		tmp.m[3][2] -= *(float*) (observer + 0x54);
		tmp.m[3][0] -= *(float*) (observer + 0x78);
		tmp.m[3][1] -= *(float*) (observer + 0x7c);
		tmp.m[3][2] -= *(float*) (observer + 0x80);
		fcn_005eb970(out, &tmp, (D3_MAT4X4*) (observer + 0x18c));
	} else {
		d3_BuildViewMatrix(node, flag, &id, out);
	}
}
