// FUNCTION: GOLD 0x4f1660
// SIZE: 144
// FUNCTION: GOLDTL 0x004f3770
// SIZE: 144

extern char* g_773da8;
extern float g_662914;
extern float g_6628a8;

float __cdecl fcn_004f3800(char* o);
void __cdecl fcn_004c5480(int id, int kind, float v);

int __cdecl fcn_004f3770(char* p)
{
	char* o;
	float d;
	float w;

	if (p == 0 || p[2] != 0x14 || p[8] == 0) {
		return 0;
	}
	o = *(char**) (p + 0x16c);
	if (o != 0 && *(unsigned short*) (o + 0x27) != 0xffff && *(unsigned short*) (o + 0x27) != *((unsigned short*)g_773da8)) {
		d = *(float*) (p + 0x14) - fcn_004f3800(o) * g_662914;
		w = *(float*) (p + 0x1c) - d;
		fcn_004c5480(*(int*) (p + 4), 0x1c, -d);
		if (!(w <= g_6628a8)) {
			return 0;
		}
	} else {
		fcn_004c5480(*(int*) (p + 4), 0x1c, -1000.0f);
	}
	return 1;
}
