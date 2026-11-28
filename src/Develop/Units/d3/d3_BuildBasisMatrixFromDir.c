#include <math.h>

extern float d3_BasisUpX;
extern float d3_BasisUpY;
extern float d3_BasisUpZ;
extern float g_662ce8;
extern float d3_UnitAxisVectors[3];

void __cdecl d3_NormalizeVector(float*);

/* ADDRESS: GOLDTL 0x00451500 */
void __cdecl d3_BuildBasisMatrixFromDir(float* dir, float angle, float* mat)
{
	float s;
	float c;
	float v[4];
	float t;
	float dotOffset;

	v[2] = d3_BasisUpZ;
	s = (float) sin(angle);
	c = (float) cos(angle);
	v[0] = d3_BasisUpX * c - d3_BasisUpY * s;
	v[1] = d3_BasisUpX * s + d3_BasisUpY * c;
	mat[8] = dir[0];
	mat[9] = dir[1];
	mat[10] = dir[2];
	d3_NormalizeVector(mat + 8);
	dotOffset = -(v[0] * mat[8] + v[2] * mat[10] + v[1] * mat[9]);
	mat[4] = dotOffset * mat[8] + v[0];
	mat[5] = dotOffset * mat[9] + v[1];
	mat[6] = dotOffset * mat[10] + v[2];
	if ((float) sqrt(mat[6] * mat[6] + mat[4] * mat[4] + mat[5] * mat[5]) < g_662ce8) {
		t = -mat[9];
		mat[4] = t * mat[8] + d3_BasisUpX;
		mat[5] = t * mat[9] + d3_BasisUpY;
		mat[6] = t * mat[10] + d3_BasisUpZ;
		if ((float) sqrt(mat[6] * mat[6] + mat[4] * mat[4] + mat[5] * mat[5]) < g_662ce8) {
			t = -mat[10];
			mat[4] = t * mat[8] + d3_UnitAxisVectors[0];
			mat[5] = t * mat[9] + d3_UnitAxisVectors[1];
			mat[6] = t * mat[10] + d3_UnitAxisVectors[2];
			if ((float) sqrt(mat[6] * mat[6] + mat[4] * mat[4] + mat[5] * mat[5]) < g_662ce8) {
				mat[0xe] = 0.0f;
				mat[0xd] = 0.0f;
				mat[0xc] = 0.0f;
				mat[0xb] = 0.0f;
				mat[9] = 0.0f;
				mat[8] = 0.0f;
				mat[7] = 0.0f;
				mat[6] = 0.0f;
				mat[4] = 0.0f;
				mat[3] = 0.0f;
				mat[2] = 0.0f;
				mat[1] = 0.0f;
				mat[0xf] = 1.0f;
				mat[10] = 1.0f;
				mat[5] = 1.0f;
				mat[0] = 1.0f;
				return;
			}
		}
	}
	d3_NormalizeVector(mat + 4);
	mat[0xb] = 0.0f;
	mat[7] = 0.0f;
	mat[3] = 0.0f;
	mat[0xf] = 1.0f;
	mat[0] = mat[5] * mat[10] - mat[9] * mat[6];
	mat[1] = mat[8] * mat[6] - mat[4] * mat[10];
	mat[2] = mat[4] * mat[9] - mat[8] * mat[5];
}
