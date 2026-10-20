extern float g_6628d8;
extern float g_662d70;
extern float g_662d74;
extern float g_662d78;

void __cdecl fcn_004518a0(float* v);
int __cdecl fcn_00451840(float* a, float* b, float eps);
void __cdecl fcn_00438c40(char* o, float* v);
void __cdecl fcn_00438b40(char* p, float* v);

/* ADDRESS: GOLDTL 0x00405760 */
void __cdecl fcn_00405760(unsigned char* e)
{
	float v[3];
	char* p;

	if (e[0x110] == 0) {
		return;
	}
	p = *(char**) (e + 0x34);
	v[0] = *(float*) (p + 0x4c);
	v[1] = *(float*) (p + 0x50);
	v[2] = *(float*) (p + 0x54);
	v[0] += *(float*) (p + 0x78);
	v[1] += *(float*) (p + 0x7c);
	v[2] += *(float*) (p + 0x80);
	v[0] = *(float*) (e + 0x114) - v[0];
	v[1] = *(float*) (e + 0x118) - v[1];
	v[2] = *(float*) (e + 0x11c) - v[2];
	fcn_004518a0(v);
	p = *(char**) (e + 0x34);
	v[0] *= g_6628d8;
	v[1] *= g_6628d8;
	v[2] *= g_6628d8;
	v[0] += *(float*) (p + 0x78);
	v[1] += *(float*) (p + 0x7c);
	v[2] += *(float*) (p + 0x80);
	fcn_00438c40(p, v);
	p = *(char**) (e + 0x34);
	v[0] += *(float*) (p + 0x4c);
	v[1] += *(float*) (p + 0x50);
	v[2] += *(float*) (p + 0x54);
	if (e[0x110] > 0) {
		e[0x110]--;
	}
	if (fcn_00451840(v, (float*) (e + 0x114), 0.4f) == 0) {
		return;
	}
	e[0x110] = 0;
	*(float*) (e + 0x114) = g_662d70;
	*(float*) (e + 0x118) = g_662d74;
	*(float*) (e + 0x11c) = g_662d78;
	fcn_00438c40(*(char**) (e + 0x34), &g_662d70);
	fcn_00438b40(*(char**) (e + 0x34), v);
}
