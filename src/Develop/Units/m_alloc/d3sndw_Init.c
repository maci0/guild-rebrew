


#include <math.h>

extern unsigned short g_6b5d18;
extern float* d3snd_ProbeSinTable;
extern char* d3sndw_SlotWaterIds;
extern char* d3sndw_SlotStates;
extern char g_67779c[];
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

int __cdecl d3sndw_Init(unsigned short n)
{
	int cnt;
	int len;
	int len2;
	float a;
	float step;
	int size;
	unsigned short i;

	if (n > 4) {
		g_6b5d18 = n;
		cnt = n;
		size = n * 4;
		d3snd_ProbeSinTable = (float*) m_alloc(size, g_67779c);
		if (d3snd_ProbeSinTable != 0) {
			d3sndw_SlotWaterIds = (char*) m_alloc(size, g_67779c);
			if (d3sndw_SlotWaterIds != 0) {
				len = size;
				__asm {
					mov edi, d3sndw_SlotWaterIds
					mov ebx, len
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
				d3sndw_SlotStates = (char*) m_alloc(size, g_67779c);
				if (d3sndw_SlotStates != 0) {
					a = 0;
					step = 6.2831855f / (float) cnt;
					len2 = size;
					__asm {
						mov edi, d3sndw_SlotStates
						mov ebx, len2
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
					for (i = 0; i < n; i++) {
						d3snd_ProbeSinTable[i] = (float) sin(a);
						a += step;
					}
					return 1;
				}
				m_FreeTracked(d3sndw_SlotWaterIds);
				d3sndw_SlotWaterIds = 0;
				m_FreeTracked(d3snd_ProbeSinTable);
				d3sndw_SlotWaterIds = 0;
				d3snd_ProbeSinTable = 0;
				return 0;
			}
			m_FreeTracked(d3snd_ProbeSinTable);
			d3snd_ProbeSinTable = 0;
		}
	}
	return 0;
}
