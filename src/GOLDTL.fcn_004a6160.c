extern int g_6b8010;

void __cdecl fcn_004432d0(int mode, int a2);
void __cdecl fcn_00455350(char* obj, char* pos, float* out);
void __cdecl fcn_00414960(float* n, float* m, char* obj);

/* ADDRESS: GOLD 0x004a66f0 */
/* ADDRESS: GOLDTL 0x004a6160 */
int __cdecl fcn_004a6160(char* a, float* pa, char* b, float* pb)
{
	struct {
		float m[4];
		float n[4];
	} v;
	int saved;

	saved = g_6b8010;
	if (!a || !b || !*(char**) (a + 0x61) || !*(char**) (b + 0x61) || a == b) {
		return -1;
	}
	fcn_004432d0(0, 1);
	fcn_00455350(*(char**) (a + 0x61), *(char**) (a + 0x61) + 0x4c, pa);
	fcn_00414960(&v.n[0], &v.m[0], *(char**) (a + 0x61));
	pa[1] += (v.m[1] - v.n[1]) * 0.8f;
	fcn_00455350(*(char**) (b + 0x61), *(char**) (b + 0x61) + 0x4c, pb);
	fcn_004432d0(saved, 1);
	return 0;
}
