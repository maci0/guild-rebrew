// FUNCTION: GOLD 0x0043b860
// FUNCTION: GOLDTL 0x438cb0

extern int g_67a370;
extern int g_6b8014;

void __cdecl fcn_00438ac0(char*, int);
void __cdecl fcn_00438af0(unsigned char);
void __cdecl fcn_00451900(float*, char*);
void __cdecl fcn_00437ac0(int, char*, int, void*);
void __cdecl fcn_00456df0(void);

void __cdecl fcn_00438cb0(char* o, int* v)
{
	float n[4];
	float* p;

	fcn_00438ac0(o, 1);
	p = (float*) (o + 0x84);
	*(int*) p = v[0];
	*(int*) (o + 0x88) = v[1];
	*(int*) (o + 0x8c) = v[2];
	if (*(int*) (o + 0x218) != 3) {
		fcn_00451900(p, o + 0x18c);
		fcn_00437ac0(g_67a370, o, 0xc0, fcn_00456df0);
		return;
	}
	if (o == ((char*)g_6b8014)) {
		fcn_00438af0(0);
	}
	n[0] = -p[0];
	n[1] = -*(float*) (o + 0x88);
	n[2] = -*(float*) (o + 0x8c);
	fcn_00451900(n, o + 0x18c);
}
