// FUNCTION: GOLD 0x0058fe70
// SIZE: 123
// FUNCTION: GOLDTL 0x00598740
// SIZE: 123

extern int g_6b8010;
extern float g_662d40[];

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00455140(int, float*, float*);
float __cdecl fcn_00451380(float*, float*);

void __cdecl fcn_00598740(float* out, int obj)
{
	float v[3];
	int save;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	out[0] = 0;
	out[1] = 0;
	out[2] = 0;
	fcn_00455140(obj, g_662d40, v);
	out[1] = fcn_00451380(g_662d40, v);
	fcn_004432d0(save, 1);
}
