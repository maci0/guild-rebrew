


extern int sb_WaveDriver;
extern char* g_14cbbe4;
extern char g_14cbc20[];
extern int g_6b7d70;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* sb_Voices;
extern char g_678e2c[];
extern char g_678df0[];
extern char g_14cbae0[];
int __cdecl msx_OpenDigOutput(int* h, int a, int b, int c);
char* __cdecl m_alloc(int size, char* tag);
int __cdecl msx_AllocateSampleHandle(int h, char* slot);
long __cdecl fcn_0064e561(long* t);
void __cdecl fcn_0064d3eb(unsigned int seed);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

int __cdecl sb_Init(int id, int count, int a, int b, int c)
{
	int r;
	int i;
	int n;

	r = 0;
	if (sb_WaveDriver != 0) {
		goto fail;
	}
	g_14cbbe4 = g_14cbc20;
	if (msx_OpenDigOutput(&sb_WaveDriver, a, b, c) != 0) {
		goto fail;
	}
	g_6b7d70 = id;
	if (id == 0) {
		g_6b7d70 = 0x1fffcc;
	}
	sb_VoiceCount = count;
	sb_Voices = m_alloc(count * 0x30, g_678e2c);
	if (sb_Voices != 0) {
		n = sb_VoiceCount * 0x30;
		__asm {
			mov edi, sb_Voices
			mov ebx, n
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
		for (i = 0; i < sb_VoiceCount; i++) {
			if (msx_AllocateSampleHandle(sb_WaveDriver, sb_Voices + i * 0x30) == -1) {
				r = -1;
			}
		}
		fcn_0064d3eb(fcn_0064e561(0));
		fcn_0064d41a(g_14cbae0, g_678df0, id);
		return r;
	}
fail:
	return -1;
}
