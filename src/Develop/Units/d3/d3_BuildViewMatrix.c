void __cdecl d3_SetIdentityMatrix4x4(float*);
void __cdecl d3_ComposeNodeMatrix(int, int, float*, float*);
void __cdecl d3_MultiplyAffineMatrices(float*, float*, float*);
float* __stdcall fcn_005eb970(float*, float*, float*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00458d90 */
void __cdecl d3_BuildViewMatrix(int source, char* view, int flags, float* out)
{
    float identity[16];
    float transform[16];

    d3_SetIdentityMatrix4x4(identity);
    if (view != 0) {
        d3_ComposeNodeMatrix(source, flags, identity, transform);
        transform[12] -= *(float*) (view + 0x4c);
        transform[13] -= *(float*) (view + 0x50);
        transform[14] -= *(float*) (view + 0x54);
        transform[12] -= *(float*) (view + 0x78);
        transform[13] -= *(float*) (view + 0x7c);
        transform[14] -= *(float*) (view + 0x80);
        d3_MultiplyAffineMatrices(transform, (float*) (view + 0x18c), out);
    } else {
        d3_ComposeNodeMatrix(source, flags, identity, out);
    }
}
#else
/* ADDRESS: GOLDTL 0x00455700 */
/* ADDRESS: GOLDDE 0x0044aec0 */
void __cdecl d3_BuildViewMatrix(char* node, char flag, float* mat, float* out)
{
	float tmp[16];
	char* parent;

	parent = *(char**) (node + 0x1fc);
	if (flag != 0) {
		*(float*) (node + 0x1bc) = 0.0f;
		*(float*) (node + 0x1c0) = 0.0f;
		*(float*) (node + 0x1c4) = 0.0f;
	} else {
		mat[12] += *(float*) (node + 0x6c);
		mat[13] += *(float*) (node + 0x70);
		mat[14] += *(float*) (node + 0x74);
		*(float*) (node + 0x1bc) = *(float*) (node + 0x4c) - *(float*) (node + 0x6c) + *(float*) (node + 0x78);
		*(float*) (node + 0x1c0) = *(float*) (node + 0x50) - *(float*) (node + 0x70) + *(float*) (node + 0x7c);
		*(float*) (node + 0x1c4) = *(float*) (node + 0x54) - *(float*) (node + 0x74) + *(float*) (node + 0x80);
	}
	if (parent != 0) {
		fcn_005eb970(tmp, mat, (float*) (node + 0x18c));
		d3_BuildViewMatrix(parent, flag, tmp, out);
	} else {
		fcn_005eb970(out, mat, (float*) (node + 0x18c));
	}
}
#endif
