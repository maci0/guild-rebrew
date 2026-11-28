#include <string.h>
extern int msx_Initialized, msx_SampleHandleLimit;
extern int* msx_WaveDrivers[16];
extern int* msx_SampleHandles[16];
extern int* msx_StreamHandles[16];

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* ptr);
int __cdecl msx_FindFreeWaveDriver(void);
int __cdecl msx_CountActiveWaveDrivers(void);
int __cdecl msx_SetSampleHandleLimit(int);
__declspec(dllimport) unsigned int __stdcall AIL_waveOutOpen(void* driver, int direct_sound, int device, void* format);
__declspec(dllimport) int __stdcall AIL_get_preference(int);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0042a120 */
int __cdecl msx_OpenDigOutput(int* out, int channels, int bits, int rate)
{
	char* rec;
	int index;
	int block;
	int loaded;

	*out = 0;
	if (msx_Initialized == 0) {
		goto fail;
	}
	index = msx_FindFreeWaveDriver();
	if (index < 0) {
		goto fail;
	}
	rec = m_alloc(0x1c, (char*) 0x679874);
	msx_WaveDrivers[index] = (int*) rec;
	*(short*) ((char*) msx_WaveDrivers[index] + 4) = 1;
	*(short*) ((char*) msx_WaveDrivers[index] + 6) = (short) channels;
	*(int*) ((char*) msx_WaveDrivers[index] + 8) = rate;
	block = (unsigned int) bits >> 3;
	loaded = block * channels;
	*(int*) ((char*) msx_WaveDrivers[index] + 0xc) = block * channels * rate;
	*(short*) ((char*) msx_WaveDrivers[index] + 0x10) = (short) loaded;
	*(short*) ((char*) msx_WaveDrivers[index] + 0x12) = (short) bits;
	if (AIL_waveOutOpen(msx_WaveDrivers[index], 0, 0, (char*) msx_WaveDrivers[index] + 4) != 0) {
		m_FreeTracked(msx_WaveDrivers[index]);
		msx_WaveDrivers[index] = 0;
fail:
		return -1;
	}
	if (msx_CountActiveWaveDrivers() == 1 && msx_SampleHandleLimit == 0) {
		msx_SetSampleHandleLimit(AIL_get_preference(1));
	}
	msx_SampleHandles[index] = m_alloc(msx_SampleHandleLimit * 4, (char*) 0x679874);
	msx_StreamHandles[index] = m_alloc(msx_SampleHandleLimit * 4, (char*) 0x679874);
	/* Reviewed native fill cores at 0x0042a24a-0x0042a26a and 0x0042a284-0x0042a2a4. */
	{


		bits = msx_SampleHandleLimit * 4;
		channels = (int) msx_SampleHandles[index];
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
		bits = msx_SampleHandleLimit * 4;
		channels = (int) msx_StreamHandles[index];
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
	*(int*) ((char*) msx_WaveDrivers[index] + 0x18) = msx_SampleHandleLimit;
	*(int*) ((char*) msx_WaveDrivers[index] + 0x14) = 0;
	*out = (int) msx_WaveDrivers[index];
	return 0;
}
