#include <string.h>
extern volatile int gm_GameTicks;
#include "../d3/d3_animation.h"
void __cdecl d3_FreeObjectAnimation(char* a0);
char* __cdecl m_alloc(unsigned int size, char* file);
int __cdecl d3_StepAnimFrame(D3_ANIMATION_OPTIONS flags, int v, int lo, int hi, int max);
void __cdecl d3_BuildAnimSplineTangents(void* a0);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004339e0 */
int* __cdecl d3_CreateObjectAnimation(char* a0, D3_ANIMATION_OPTIONS flags, int frameCount, void* srcFrames)
{
	int* animation;
	int* v3;
	int v6;
	int i;
	int copy_count;

	animation = 0;
	if (*(int*) (a0 + 0x1d0) != 0) {
		d3_FreeObjectAnimation(a0);
	}
	if (*(int*) (a0 + 0x218) == 4 || *(int*) (a0 + 0x218) == 3) {
		animation = (int*) m_alloc(0x44, (char*) 0x67a0f8);
		animation[0] = frameCount;
		*(D3_ANIMATION_OPTIONS*) (animation + 0xb) = flags;
		animation[4] = 100;
		animation[0xe] = 0x3f800000;
		
		animation[0xf] = 0;
		
		*(unsigned char*) ((char*) animation + 0x2d) = *(unsigned char*) ((char*) animation + 0x2d) & 0xdf;
		*(unsigned char*) ((char*) animation + 0x34) = *(unsigned char*) ((char*) animation + 0x34) & 0xdf | 0x10;
		v3 = (int*) m_alloc(frameCount * 0x58, (char*) 0x67a0dc);
		animation[0x10] = (int) v3;
		copy_count = *animation * 0x58;
		__asm {
			mov edi, v3
			mov esi, srcFrames
			mov ebx, copy_count
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L_copy_tail
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L_copy_tail:
			add ecx, ebx
			rep movsb
		}
		*(int*) (animation[0x10] - 0x58 + *animation * 0x58) = *(int*) (animation[0x10] + *animation * 0x58 - 0xb0);
		for (i = 0; i < *animation; i++) {
			int* e;

			e = (int*) (animation[0x10] + i * 0x58);
			*e = *e * 3;
		}
		animation[5] = *(int*) (a0 + 0x4c);
		animation[6] = *(int*) (a0 + 0x50);
		animation[7] = *(int*) (a0 + 0x54);
		animation[8] = *(int*) (a0 + 0x84);
		animation[9] = *(int*) (a0 + 0x88);
		animation[10] = *(int*) (a0 + 0x8c);
		if ((*(unsigned char*) ((char*) animation + 0x2d) & 2) == 0) {
			animation[1] = 0;
			animation[3] = 0;
			animation[2] = 1;
		} else {
			v6 = *animation - 1;
			animation[1] = v6;
			animation[3] = *(int*) (animation[0x10] + v6 * 0x58) - 1;
			animation[2] = d3_StepAnimFrame(*(D3_ANIMATION_OPTIONS*) (animation + 0xb), v6, 0, v6, v6);
		
		}
		d3_BuildAnimSplineTangents(animation);
	}
	*(int**) (a0 + 0x1d0) = animation;
	*(int*) (a0 + 0x40) = gm_GameTicks;
	return animation;
}
