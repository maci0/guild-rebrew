#include <stdlib.h>

extern int g_6b7fac;
extern char* g_6b8014;

void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLD 0x00413b30 */
int* __cdecl fcn_00413b30(int count)
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
	if (g_6b8014 != 0) {
		info[16] = *(int*) (g_6b8014 + 0x84);
		info[17] = *(int*) (g_6b8014 + 0x88);
		info[18] = *(int*) (g_6b8014 + 0x8c);
		info[20] = *(int*) (g_6b8014 + 0x4c);
		info[21] = *(int*) (g_6b8014 + 0x50);
		info[22] = *(int*) (g_6b8014 + 0x54);
	}
	capacity = count;
	if (capacity <= 0) {
		capacity = 1;
	}
	drop = (float*) m_alloc(capacity * 0x28, "d3t:RainDropList");
	info[4] = (int) drop;
	if (drop == 0) {
		m_FreeTracked(info);
		return 0;
	}
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
