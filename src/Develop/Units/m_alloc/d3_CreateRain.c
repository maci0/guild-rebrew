#include <stdlib.h>

extern volatile int g_6b7fac;
extern char* d3_ActiveCamera;

void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLD 0x00413b30 */
/* ADDRESS: GOLDTL 0x00415310 */
int* __cdecl d3_CreateRain(int count)
{
	int* info;
	float* drop;
	int capacity;
	int i;
	double value;
	info = (int*) m_alloc(0x60, "d3t:RainInfo");
	i = 0;
	if (info == 0) {
		return 0;
	}
	info[0] = count;
	info[1] = count;
	info[2] = count;
	info[3] = count;
	info[5] = 0x3f800000;
	info[6] = 0;
	info[7] = 0x3f800000;
	info[8] = 0;
	info[9] = 0x3f800000;
	info[10] = 0;
	info[11] = g_6b7fac;
	info[12] = g_6b7fac;
	info[13] = g_6b7fac;
	info[14] = g_6b7fac;
	info[15] = g_6b7fac;
	if (d3_ActiveCamera != 0) {
		info[16] = *(int*) (d3_ActiveCamera + 0x84);
		info[17] = *(int*) (d3_ActiveCamera + 0x88);
		info[18] = *(int*) (d3_ActiveCamera + 0x8c);
		info[20] = *(int*) (d3_ActiveCamera + 0x4c);
		info[21] = *(int*) (d3_ActiveCamera + 0x50);
		info[22] = *(int*) (d3_ActiveCamera + 0x54);
	}
	capacity = count;
	if (capacity < 1) {
		capacity = 1;
	}
	if ((info[4] = (int) m_alloc(capacity * 0x28, "d3t:RainDropList")) == 0) {
		m_FreeTracked(info);
		return 0;
	}
	drop = (float*) info[4];
	while (i < *info) {
		value = rand() * 3.0518509447574615e-5f - 0.5f;
		drop[0] = value + value;
		value = rand() * 3.0518509447574615e-5f - 0.5f;
		drop[1] = value + value;
		value = rand() * 3.0518509447574615e-5f - 0.5f;
		drop[2] = value + value;
		drop[3] = rand() * 7.629627361893654e-6f + 0.25f;
		drop[4] = rand() * 1.5259255405908334e-6f + 0.25f;
		drop[5] = rand() * 1.5259255405908334e-6f + 0.25f;
		drop += 10;
		i++;
	}
	return info;
}
