#include <string.h>

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* ptr);
int __cdecl fcn_0042b100(void);
int __cdecl fcn_0042b2c0(void);
int __cdecl fcn_0042a4d0(int);
__declspec(dllimport) unsigned int __stdcall AIL_waveOutOpen(void* driver, int direct_sound, int device, void* format);
__declspec(dllimport) int __stdcall AIL_get_preference(int);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0042a120 */
int __cdecl fcn_0042a120(int* out, int channels, int bits, int rate)
{
	char* rec;
	int index;
	int block;
	int loaded;

	*out = 0;
	if (*(int*) 0x6b7f90 == 0) {
		return -1;
	}
	index = fcn_0042b100();
	if (index < 0) {
		return -1;
	}
	rec = m_alloc(0x1c, (char*) 0x679874);
	*(int*) ((char*) 0x6b7ed0 + index * 4) = (int) rec;
	*(short*) (rec + 4) = 1;
	*(short*) (rec + 6) = (short) channels;
	*(int*) (rec + 8) = rate;
	block = bits >> 3;
	loaded = block * channels;
	*(int*) (rec + 0xc) = loaded * rate;
	*(short*) (rec + 0x10) = (short) loaded;
	*(short*) (rec + 0x12) = (short) bits;
	if (AIL_waveOutOpen(rec, 0, 0, rec + 4) != 0) {
		m_FreeTracked(rec);
		*(int*) ((char*) 0x6b7ed0 + index * 4) = 0;
		return -1;
	}
	if (fcn_0042b2c0() == 1 && *(int*) 0x6b7f94 == 0) {
		fcn_0042a4d0(AIL_get_preference(1));
	}
	*(int*) ((char*) 0x6b7f10 + index * 4) = (int) m_alloc(*(int*) 0x6b7f94 * 4, (char*) 0x679874);
	*(int*) ((char*) 0x6b7f50 + index * 4) = (int) m_alloc(*(int*) 0x6b7f94 * 4, (char*) 0x679874);
	memset((void*) *(int*) ((char*) 0x6b7f10 + index * 4), 0, *(int*) 0x6b7f94 * 4);
	memset((void*) *(int*) ((char*) 0x6b7f50 + index * 4), 0, *(int*) 0x6b7f94 * 4);
	*(int*) (rec + 0x18) = *(int*) 0x6b7f94;
	*(int*) (rec + 0x14) = 0;
	*out = (int) rec;
	return 0;
}
