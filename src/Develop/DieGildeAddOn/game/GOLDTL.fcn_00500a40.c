#include <string.h>

extern char g_7f4ca0[];
extern char g_99f620[];
extern int g_99f624[9];
extern float g_99f644;
extern float g_99f648[8];
extern float g_99f668[8];
extern float g_662cf8;
extern float g_6628a8;

float __cdecl fcn_00505e30(int);
int __cdecl fcn_004fffb0(int);
float __cdecl fcn_004fef80(void*);
float __cdecl fcn_004feff0(void*);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* ADDRESS: GOLDTL 0x00500a40 */
void __cdecl fcn_00500a40(void)
{
	char* p;
	int i;
	int idx;


	p = g_7f4ca0;
	memset(g_99f620, 0, 0x68);
	i = 0;
	do {
		if (*(short*) p != -1
		    && *(unsigned char*) (p + 8) > 0
		    && *(unsigned char*) (p + 2) < 0xa) {
			*(int*) &g_99f620[0] += 1;
			idx = (int) MAX(MIN(fcn_00505e30(i) * 0.1f, 7.0f), g_6628a8);
			g_99f624[idx] += 1;
			if (fcn_004fffb0(i) != 0)
				g_99f644 += 1.0f;
			g_99f648[idx] += fcn_004fef80(p);
			g_99f668[idx] += fcn_004feff0(p);
		}
		p += 0x21c;
		i++;
	} while ((int) p < 0x85a0a0);
	for (p = g_99f620 + 0x48; (int) p < (int) (g_99f620 + 0x68); p += 4) {
		*(float*) (p - 0x20) = (*(float*) (p - 0x20) / *(float*) p) * g_662cf8;
		*(float*) p = *(float*) p / (float) *(int*) (p - 0x44);
	}
	g_99f644 = (g_99f644 / (float) *(int*) &g_99f620[0]) * g_662cf8;
}
