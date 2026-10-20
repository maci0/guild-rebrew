extern int g_772848;
extern int g_77284c;
extern int g_772894;
extern int g_772898;
extern int g_77289c;
extern int g_7728b4;
extern int g_7728b8;
extern float g_772850;
extern float g_772854;
extern float g_772858;
extern float g_772860;
extern float g_772864;
extern float g_772868;
extern float g_772870;
extern float g_772874;
extern float g_772878;
extern float g_772880;
extern float g_772884;
extern float g_772888;
extern float g_662910;
extern float g_662914;
extern float g_662a98;
extern float g_662c98;
extern float g_66444c;
extern float g_664450;
extern float g_6660f4;

void __cdecl fcn_004f11c0(char* p, float* o1, float* o2);
float __cdecl fcn_004f1290(char* p);
int __cdecl fcn_005e8e80(char* o, float* pos, float* dir, float speed, float b, float a);
int __cdecl fcn_005e8fe0(float* p, float spread, float* dir, float lift, float* up, float scale);
float __cdecl fcn_004f0eb0(int level, int percent, int count, int a4, int a5);
int __cdecl fcn_004f0a30(char* a0, char* a1, float* a2, float* a3, float* a4, float a5);

/* ADDRESS: GOLDTL 0x004a6550 */
int __cdecl fcn_004a6550(char* a0, char* a1)
{
	char buf1[104];
	char buf2[104];
	char buf3[104];
	float pos[3];
	float pos2[3];
	float pos3[3];
	float f;
	float spread;
	float scale;
	float speed;
	float tx;
	float ty;
	float tz;
	float mx;
	unsigned int bits;
	float* entry;
	int kind;
	int p1;
	int p2;

	if (g_772848 != *(int*) (a0 + 4) || g_77284c != *(int*) (a1 + 1)) {
		return 0;
	}
	fcn_004f11c0(a1, &spread, &scale);
	f = fcn_004f1290(a1);
	p2 = g_7728b8;
	p1 = g_7728b4;
	entry = (float*) (g_77289c * 0xc + 0x665288);
	bits = *(unsigned int*) (g_77289c * 0xc + 0x665290);
	speed = (float) g_772898 * g_662910
		* (f * *(float*) (g_77289c * 0xc + 0x66528c) - *entry) + *entry;
	kind = g_772894;
	if (kind == 1) {
		pos[0] = g_772850 + g_772860 * g_662914;
		pos[1] = g_772854 + g_772864 * g_662914;
		pos[2] = g_772858 + g_772868 * g_662914;
		fcn_005e8e80(buf1, pos, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		f = fcn_004f0eb0(g_77289c, g_772898, 1, p1, p2);
		fcn_004f0a30(a1, a0, (float*) buf1, 0, 0, f);
		return 1;
	}
	if (kind == 2) {
		pos2[0] = g_772860 * g_662c98 + g_772850;
		pos2[1] = g_772854 + g_772864 * g_662c98;
		pos2[2] = g_772868 * g_662c98 + g_772858;
		pos3[0] = g_772874 * g_662a98;
		pos[0] = g_772870 * g_662a98 + pos2[0];
		pos[1] = pos3[0] + pos2[1];
		pos[2] = g_772878 * g_662a98 + pos2[2];
		pos3[1] = g_772878 * g_664450;
		pos2[0] = g_772870 * g_664450 + pos2[0];
		pos2[1] = g_772874 * g_664450 + pos2[1];
		pos3[2] = pos3[1] + pos2[2];
		fcn_005e8e80(buf2, pos, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8e80(buf1, pos2, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8fe0((float*) buf2, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		f = fcn_004f0eb0(g_77289c, g_772898, 2, p1, p2);
		fcn_004f0a30(a1, a0, (float*) buf2, (float*) buf1, 0, f);
		return 1;
	}
	if (kind == 3) {
		tx = g_772860 * g_662c98 + g_772850;
		ty = g_772864 * g_662c98 + g_772854;
		tz = g_772868 * g_662c98 + g_772858;
		pos[0] = g_772880 * g_662a98 + tx;
		pos[1] = g_772884 * g_662a98 + ty;
		pos[2] = g_772888 * g_662a98 + tz;
		mx = g_772880 * g_66444c;
		pos3[0] = g_772870 * g_662a98 + tx + mx;
		pos3[1] = g_772874 * g_662a98 + g_772884 * g_66444c + ty;
		pos3[2] = g_772878 * g_662a98 + g_772888 * g_66444c + tz;
		pos2[0] = g_772870 * g_664450 + mx + tx;
		pos2[1] = g_772874 * g_664450 + g_772884 * g_66444c + ty;
		pos2[2] = g_772878 * g_664450 + g_772888 * g_66444c + tz;
		fcn_005e8e80(buf3, pos3, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8e80(buf1, pos2, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8e80(buf2, pos, (float*) 0x772860, speed,
			*(float*) &bits, g_6660f4);
		fcn_005e8fe0((float*) buf3, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf2, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		f = fcn_004f0eb0(g_77289c, g_772898, 3, p1, p2);
		fcn_004f0a30(a1, a0, (float*) buf3, (float*) buf1, (float*) buf2, f);
		return 1;
	}
	return 0;
}
