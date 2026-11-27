extern float g_6628d8;
extern float g_662d70;
extern float g_662d74;
extern float g_662d78;

void __cdecl d3_NormalizeVector(float* v);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d3_SetObjectPosition(char* o, float* v);
void __cdecl d3_SetNodePosition(char* p, float* v);

/* ADDRESS: GOLDTL 0x00405760 */
void __cdecl ch_StepToTargetPosition(unsigned char* e)
{
	float v[4];
	float x;
	float y;
	float sy;
	float sz;
	char* p;

	if (e[0x110] == 0) {
		return;
	}
	p = *(char**) (e + 0x34);
	x = *(float*) (p + 0x4c);
	y = *(float*) (p + 0x50);
	*(int*) &v[2] = *(int*) (p + 0x54);
	v[0] = x + *(float*) (p + 0x78);
	sy = y + *(float*) (p + 0x7c);
	sz = v[2] + *(float*) (p + 0x80);
	v[0] = *(float*) (e + 0x114) - v[0];
	v[1] = *(float*) (e + 0x118) - sy;
	v[2] = *(float*) (e + 0x11c) - sz;
	d3_NormalizeVector(v);
	p = *(char**) (e + 0x34);
	v[0] *= 0.4f;
	v[1] *= 0.4f;
	v[2] *= 0.4f;
	v[0] += *(float*) (p + 0x78);
	v[1] += *(float*) (p + 0x7c);
	v[2] += *(float*) (p + 0x80);
	d3_SetObjectPosition(p, v);
	p = *(char**) (e + 0x34);
	v[0] += *(float*) (p + 0x4c);
	v[1] += *(float*) (p + 0x50);
	v[2] += *(float*) (p + 0x54);
	if (e[0x110] > 0) {
		e[0x110]--;
	}
	if (CompareVector3WithinTolerance(v, (float*) (e + 0x114), 0.4f) == 0) {
		return;
	}
	e[0x110] = 0;
	*(float*) (e + 0x114) = g_662d70;
	*(float*) (e + 0x118) = g_662d74;
	*(float*) (e + 0x11c) = g_662d78;
	d3_SetObjectPosition(*(char**) (e + 0x34), &g_662d70);
	d3_SetNodePosition(*(char**) (e + 0x34), v);
}
