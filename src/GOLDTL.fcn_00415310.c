#include <stdlib.h>

#include "Develop/Units/d3/d3_camera.h"

extern char g_677580[];
extern char g_67756c[];
extern float g_662a18;
extern float g_6628bc;
extern float g_6628cc;
extern float g_662a40;
extern float g_662a44;

void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00415310 */
int* __cdecl fcn_00415310(int count)
{
	int* rain;
	char* cam;
	float* drop;
	int i;
	int n;

	rain = (int*) m_alloc(0x60, g_677580);
	if (rain == 0) {
		return 0;
	}
	rain[0] = count;
	rain[1] = count;
	rain[2] = count;
	rain[3] = count;
	rain[5] = 0x3f800000;
	rain[6] = 0;
	rain[7] = 0x3f800000;
	rain[8] = 0;
	rain[9] = 0x3f800000;
	rain[10] = 0;
	rain[11] = *(int*) 0x6b7fac;
	rain[12] = *(int*) 0x6b7fac;
	rain[13] = *(int*) 0x6b7fac;
	rain[14] = *(int*) 0x6b7fac;
	rain[15] = *(int*) 0x6b7fac;
	cam = *(char**) 0x6b8014;
	if (cam != 0) {
		rain[16] = *(int*) (cam + 0x84);
		cam = *(char**) 0x6b8014;
		rain[17] = *(int*) (cam + 0x88);
		cam = *(char**) 0x6b8014;
		rain[18] = *(int*) (cam + 0x8c);
		cam = *(char**) 0x6b8014;
		rain[20] = *(int*) (cam + 0x4c);
		cam = *(char**) 0x6b8014;
		rain[21] = *(int*) (cam + 0x50);
		cam = *(char**) 0x6b8014;
		rain[22] = *(int*) (cam + 0x54);
	}
	n = count;
	if (n < 1) {
		n = 1;
	}
	rain[4] = (int) m_alloc(n * 0x28, g_67756c);
	if (rain[4] == 0) {
		m_FreeTracked(rain);
		return 0;
	}
	drop = (float*) rain[4];
	if (rain[0] > 0) {
		i = 0;
		do {
			drop[0] = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
			drop[1] = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
			drop[2] = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
			drop[3] = (float) rand() * g_662a44 + g_6628bc;
			drop[4] = (float) rand() * g_662a40 + g_6628bc;
			drop[5] = (float) rand() * g_662a40 + g_6628bc;
			drop += 10;
			i++;
		} while (i < rain[0]);
	}
	return rain;
}
