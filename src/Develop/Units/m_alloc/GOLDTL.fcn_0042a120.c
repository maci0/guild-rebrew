#include <string.h>
extern int g_6b7f90, g_6b7f94;
extern int* g_6b7ed0[16];
extern int* g_6b7f10[16];
extern int* g_6b7f50[16];

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
	if (g_6b7f90 == 0) {
		goto fail;
	}
	index = fcn_0042b100();
	if (index < 0) {
		goto fail;
	}
	rec = m_alloc(0x1c, (char*) 0x679874);
	g_6b7ed0[index] = (int*) rec;
	*(short*) ((char*) g_6b7ed0[index] + 4) = 1;
	*(short*) ((char*) g_6b7ed0[index] + 6) = (short) channels;
	*(int*) ((char*) g_6b7ed0[index] + 8) = rate;
	block = (unsigned int) bits >> 3;
	loaded = block * channels;
	*(int*) ((char*) g_6b7ed0[index] + 0xc) = loaded * rate;
	*(short*) ((char*) g_6b7ed0[index] + 0x10) = (short) loaded;
	*(short*) ((char*) g_6b7ed0[index] + 0x12) = (short) bits;
	if (AIL_waveOutOpen(g_6b7ed0[index], 0, 0, (char*) g_6b7ed0[index] + 4) != 0) {
		m_FreeTracked(g_6b7ed0[index]);
		g_6b7ed0[index] = 0;
fail:
		return -1;
	}
	if (fcn_0042b2c0() == 1 && g_6b7f94 == 0) {
		fcn_0042a4d0(AIL_get_preference(1));
	}
	g_6b7f10[index] = m_alloc(g_6b7f94 * 4, (char*) 0x679874);
	g_6b7f50[index] = m_alloc(g_6b7f94 * 4, (char*) 0x679874);
	/* Reviewed native fill cores at 0x0042a24a-0x0042a26a and 0x0042a284-0x0042a2a4. */
	{


		bits = g_6b7f94 * 4;
		channels = (int) g_6b7f10[index];
		__asm {
			mov edi, channels
			mov ebx, bits
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		bits = g_6b7f94 * 4;
		channels = (int) g_6b7f50[index];
		__asm {
			mov edi, channels
			mov ebx, bits
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	*(int*) ((char*) g_6b7ed0[index] + 0x18) = g_6b7f94;
	*(int*) ((char*) g_6b7ed0[index] + 0x14) = 0;
	*out = (int) g_6b7ed0[index];
	return 0;
}
