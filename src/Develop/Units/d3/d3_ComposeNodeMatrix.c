void __cdecl d3_MultiplyAffineMatrices(float* a, float* b, float* output);

/* Composes the object's matrix (+0x18c) with m and recurses up the parent
 * chain (+0x1f8). Unless flags is set, the +0x6c offset is added to the
 * translation of m and the pivot (+0x1bc) is position - offset + base. */

/* ADDRESS: GOLD 0x00458cd0 */
void __cdecl d3_ComposeNodeMatrix(char* o, int flags, float* m, float* out)
{
	float t[16];
	char* parent;

	parent = *(char**) (o + 0x1f8);
	if ((char) flags) {
		*(int*) (o + 0x1bc) = 0;
		*(int*) (o + 0x1c0) = 0;
		*(int*) (o + 0x1c4) = 0;
	} else {
		m[12] += *(float*) (o + 0x6c);
		m[13] += *(float*) (o + 0x70);
		m[14] += *(float*) (o + 0x74);
		*(float*) (o + 0x1bc) = *(float*) (o + 0x4c) - *(float*) (o + 0x6c)
			+ *(float*) (o + 0x78);
		*(float*) (o + 0x1c0) = *(float*) (o + 0x50) - *(float*) (o + 0x70)
			+ *(float*) (o + 0x7c);
		*(float*) (o + 0x1c4) = *(float*) (o + 0x54) - *(float*) (o + 0x74)
			+ *(float*) (o + 0x80);
	}
	if (parent != 0) {
		d3_MultiplyAffineMatrices(m, (float*) (o + 0x18c), t);
		d3_ComposeNodeMatrix(parent, flags, t, out);
	} else {
		d3_MultiplyAffineMatrices(m, (float*) (o + 0x18c), out);
	}
}
