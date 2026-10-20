#include <math.h>


extern int g_67a370;
extern int g_6b8300;
extern int g_772e9c;
extern int g_772ec4;

int __cdecl fcn_004ce590(int a1);
int __cdecl fcn_00418000(int a1, float* v, int n, float f1, float f2,
    float f3, float f4, float f5, float f6, float* out, int a11, int a12,
    float f13);
int* __cdecl fcn_004185a0(int a1, float* pos, int n, float f1, float f2,
    float f3, float f4, float f5, float f6, float f7, float f8, float f9);
int __cdecl fcn_00417d00(int a1, float* v, int n, float f1, float f2,
    float f3, float f4, int a8);
int __cdecl fcn_004234e0(char* bank, const char* name, int loop, int pan,
    int vol, int a, int b);
void __cdecl fcn_0045b920(int g, int x, int z, float* out);
unsigned int __cdecl fcn_004e6cb0(unsigned int n);
void __cdecl fcn_004cfc40(int a1, int a2, int a3);
int __cdecl fcn_004d4790(char* e);
int __cdecl fcn_00406340(char* e, const char* name, int param);
void __cdecl fcn_00442be0(int p);
int __cdecl fcn_0043c2c0(int m);
int __cdecl fcn_0043ef20(int m);

/* ADDRESS: GOLDTL 0x004cf6b0 */
int __cdecl fcn_004cf6b0(void)
{
	int count;
	int obj;
	float d;
	int world;
	int dmg;
	int dmg2;
	int n;
	int map;
	char* e;
	int other;
	int* p;
	int* q;
	float v8[4];
	float v7[4];

	world = *(int*) (((char*) g_67a370) + 0xb0);
	count = 0;
	obj = fcn_004ce590(0x176);
	for (p = (int*) 0x9b9ecc; (int) p < 0x9ba0cc; p += 4) {
		if (p[-3] != 0) {
			count++;
			if ((*(unsigned char*) (p[-2] + 0x2d) & 0x20) != 0) {
				v8[0] = -243.0f;
				v8[1] = -90.0f;
				v8[2] = 190.0f;
				v8[3] = 0.0f;
				v7[0] = -50.0f;
				v7[1] = 0.0f;
				v7[2] = 38.0f;
				v7[3] = 0.0f;
				v8[0] = *(float*) (p[-3] + 0x4c);
				v8[1] = *(float*) (p[-3] + 0x50);
				v8[2] = *(float*) (p[-3] + 0x54);
				fcn_00418000(0, v8, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f,
				    140.0f, 35.0f, v7, 0x190, 6, 1.5058822631835938f);
				fcn_004185a0(0, v8, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f,
				    4.0f, 7.0f, 8.0f, 1.5058822631835938f);
				fcn_00417d00(0, v8, 0x1e, 70.0f, 50.0f, 20.0f, 60.0f,
				    0x3c);
				map = *(int*) 0x6b8300;
				n = p[0] * map + p[-1];
				if (*(unsigned char*) (n + *(int*) (map + 0x14)) != 0) {
					*(unsigned char*) (n + *(int*) (*(int*) 0x6b8300 + 0x10)) += 0xfb;
					*(unsigned char*) (p[0] * *(int*) 0x6b8300 + p[-1] + *(int*) (*(int*) 0x6b8300 + 0x14)) = 0;
					fcn_0043c2c0(*(int*) 0x6b8300);
					fcn_0043ef20(*(int*) 0x6b8300);
				}
				fcn_004234e0((char*) g_772ec4, "Explosion_s", 1, 0x3f,
				    0x7f, 0, 0);
				for (q = (int*) 0x7e4260; (int) q < 0x7e42e0; q++) {
					e = (char*) *q;
					if (e != 0 && e[8] != 0) {
						other = *(int*) (e + 0x184);
						fcn_0045b920(world, p[-1], p[0], v8);
						v8[0] -= *(float*) (*(int*) (other + 0x34) + 0x4c);
						v8[1] -= *(float*) (*(int*) (other + 0x34) + 0x50);
						v8[2] -= *(float*) (*(int*) (other + 0x34) + 0x54);
						d = (float) sqrt(v8[2] * v8[2] + v8[1] * v8[1] + v8[0] * v8[0]);
						if (d < 100.0f) {
							n = (int) fcn_004e6cb0((unsigned int) ((unsigned char) ((char*) obj)[6] - (unsigned char) ((char*) obj)[5]));
							dmg = (int) ((double) (unsigned int) (n + (unsigned char) ((char*) obj)[5]) * (*(float*) (e + 0x1c) * 0.01));
							dmg2 = (int) ((double) dmg * (1.0 - d * 0.01f));
							*(int*) (e + 0x24) -= dmg2;
							fcn_004cfc40((int) e, dmg2, *(int*) (e + 0x16c) == g_772e9c ? 1 : 2);
							if (!fcn_004d4790(e)) {
								fcn_00406340((char*) other, "kampf/arm_greifen", 1);
							}
						}
					}
				}
				fcn_00442be0(p[-3]);
				p[-3] = 0;
			}
		}
	}
	return count;
}
