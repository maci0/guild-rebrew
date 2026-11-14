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
float __cdecl fcn_004f0eb0(int level, int percent, int count);
int __cdecl fcn_004f0a30(char* a0, char* a1, float* a2, float* a3, float* a4, float a5, int a6, unsigned int a7);

typedef struct {
	float x;
	float y;
	float z;
} Vec3_4a6550;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4_4a6550;

typedef struct {
	float f00;
	float f04;
	float f08;
} FxRow_4a6550;

/* ADDRESS: GOLDTL 0x004a6550 */
int __cdecl fcn_004a6550(char* a0, char* a1)
{
	char buf1[104];
	char buf2[104];
	char buf3[104];
	Vec4_4a6550 pos;
	Vec4_4a6550 delta;
	Vec4_4a6550 pos2;
	Vec3_4a6550 pos3;
	float scale;
	float spread;
	float speed;
	float bits;
	float factor;
	float tx;
	float ty;
	float tz;
	FxRow_4a6550* entry;
	int p2;
	int p1;
	int kind;

	if (g_772848 != *(int*) (a0 + 4) || g_77284c != *(int*) (a1 + 1)) {
		return 0;
	}
	fcn_004f11c0(a1, &spread, &scale);
	factor = fcn_004f1290(a1);
	p2 = g_7728b8;
	p1 = g_7728b4;
	entry = &((FxRow_4a6550*) 0x665288)[g_77289c];
	bits = entry->f08;
	speed = (factor * entry->f04 - entry->f00)
		* ((float) g_772898 * g_662910) + entry->f00;
	kind = g_772894;
	if (kind == 1) {
		pos.x = g_662914 * g_772860;
		pos.y = g_662914 * g_772864;
		pos.z = g_662914 * g_772868;
		pos.x += g_772850;
		pos.y += g_772854;
		pos.z += g_772858;
		fcn_005e8e80(buf1, &pos.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_004f0a30(a1, a0, (float*) buf1, 0, 0,
			fcn_004f0eb0(g_77289c, g_772898, 1), p2, (unsigned int) p1);
		return 1;
	}
	if (kind == 2) {
		tx = g_662c98 * g_772860;
		ty = g_662c98 * g_772864;
		tz = g_662c98 * g_772868;
		tx += g_772850;
		ty += g_772854;
		tz += g_772858;
		pos.x = tx;
		pos.y = ty;
		pos.z = tz;
		pos2.x = tx;
		pos2.y = ty;
		pos2.z = tz;
		delta.x = g_662a98 * g_772870;
		delta.y = g_662a98 * g_772874;
		delta.z = g_662a98 * g_772878;
		pos.x += delta.x;
		pos.y += delta.y;
		pos.z += delta.z;
		delta.x = g_664450 * g_772870;
		delta.y = g_664450 * g_772874;
		delta.z = g_664450 * g_772878;
		pos2.x += delta.x;
		pos2.y += delta.y;
		pos2.z += delta.z;
		fcn_005e8e80(buf2, &pos.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8e80(buf1, &pos2.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8fe0((float*) buf2, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_004f0a30(a1, a0, (float*) buf2, (float*) buf1, 0,
			fcn_004f0eb0(g_77289c, g_772898, 2), p2, (unsigned int) p1);
		return 1;
	}
	if (kind == 3) {
		tx = g_662c98 * g_772860;
		ty = g_662c98 * g_772864;
		tz = g_662c98 * g_772868;
		tx += g_772850;
		ty += g_772854;
		tz += g_772858;
		pos3.x = tx;
		pos3.y = ty;
		pos3.z = tz;
		pos2.x = tx;
		pos2.y = ty;
		pos2.z = tz;
		pos.x = tx;
		pos.y = ty;
		pos.z = tz;
		delta.x = g_662a98 * g_772880;
		delta.y = g_662a98 * g_772884;
		delta.z = g_662a98 * g_772888;
		pos.x += delta.x;
		pos.y += delta.y;
		pos.z += delta.z;
		delta.x = g_66444c * g_772880;
		delta.y = g_66444c * g_772884;
		delta.z = g_66444c * g_772888;
		pos3.x += delta.x;
		pos3.y += delta.y;
		pos3.z += delta.z;
		pos2.x += delta.x;
		pos2.y += delta.y;
		pos2.z += delta.z;
		delta.x = g_662a98 * g_772870;
		delta.y = g_662a98 * g_772874;
		delta.z = g_662a98 * g_772878;
		pos3.x += delta.x;
		pos3.y += delta.y;
		pos3.z += delta.z;
		delta.x = g_664450 * g_772870;
		delta.y = g_664450 * g_772874;
		delta.z = g_664450 * g_772878;
		pos2.x += delta.x;
		pos2.y += delta.y;
		pos2.z += delta.z;
		fcn_005e8e80(buf3, &pos3.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8e80(buf1, &pos2.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8e80(buf2, &pos.x, (float*) 0x772860, speed,
			bits, g_6660f4);
		fcn_005e8fe0((float*) buf3, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf1, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_005e8fe0((float*) buf2, spread, (float*) 0x772870, spread,
			(float*) 0x772880, scale);
		fcn_004f0a30(a1, a0, (float*) buf3, (float*) buf1, (float*) buf2,
			fcn_004f0eb0(g_77289c, g_772898, 3), p2, (unsigned int) p1);
		return 1;
	}
	return 0;
}
