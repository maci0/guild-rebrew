#include <string.h>
#include "../../Units/d3/d3_animation.h"
typedef struct FRAME_412B10 {
	unsigned int parameter;
	float position[3];
	char unknown_010[4];
	float rotation[3];
	char unknown_020[0x58 - 0x20];
} FRAME_412B10;
extern int g_6b8014;
int* __cdecl fcn_004339e0(char* a0, D3_ANIMATION_OPTIONS flags, int count, void* frames);
void __cdecl fcn_00451720(void* a0, void* a1, void* a2, void* a3);
void __cdecl fcn_00438cb0(void* a0, void* a1);

/* The native body keeps an EBP frame (/Oy-, non-frame-omitted build). */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00412b10 */
unsigned int __cdecl fcn_00412b10(char* a0, float a1, float a2, float a3, float a4, float a5, float a6, unsigned int a7, unsigned char a8)
{
	D3_ANIMATION_OPTIONS z;
	float rotation[3];
	char v6[12];
	FRAME_412B10 frames[2];
	int* v3;
	void* fill_dst;
	int fill_size;

	if (*(int*) 0x6b5cbc != 0 && (char*) g_6b8014 == a0) {
		return 0;
	}
	fill_dst = &z;
	fill_size = sizeof(z);
	__asm {
		mov edi, fill_dst
		mov ebx, fill_size
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L412b10fill
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L412b10fill:
		add ecx, ebx
		rep stosb
	}
	z.layer = z.layer | 0x14;
	z.layer = z.layer & 0xf7;
	rotation[0] = a4;
	rotation[2] = a6;
	z.queue = 1;
	frames[0].rotation[0] = 0.0f;
	frames[0].rotation[1] = 0.0f;
	frames[0].rotation[2] = 0.0f;
	frames[0].position[0] = 0.0f;
	frames[0].position[1] = 0.0f;
	frames[0].position[2] = 0.0f;
	rotation[1] = a5;
	if ((a8 & 8) != 0) {
		fcn_00451720(a0 + 0x84, rotation, v6, rotation);
		fcn_00438cb0(a0, v6);
	}
	if (a0 == (char*) g_6b8014) {
		*(float*) 0x14ce890 = rotation[0];
		*(float*) 0x14ce894 = rotation[1];
		*(float*) 0x14ce898 = rotation[2];
		*(float*) 0x14ce880 = a1;
		*(float*) 0x14ce884 = a2;
		*(float*) 0x14ce888 = a3;
	}
	frames[1].position[0] = a1 - *(float*) (a0 + 0x4c);
	frames[1].position[1] = a2 - *(float*) (a0 + 0x50);
	frames[1].position[2] = a3 - *(float*) (a0 + 0x54);
	frames[0].parameter = a7;
	rotation[0] -= *(float*) (a0 + 0x84);
	rotation[1] -= *(float*) (a0 + 0x88);
	rotation[2] -= *(float*) (a0 + 0x8c);
	frames[1].rotation[0] = rotation[0];
	frames[1].rotation[1] = rotation[1];
	frames[1].rotation[2] = rotation[2];
	v3 = fcn_004339e0(a0, z, 2, frames);
	if (a0 != (char*) g_6b8014) {
		return 1;
	}
	*(int*) 0x6b5cbc = 1;
	*(int**) 0x6b5cc0 = v3;
	*(unsigned char*) ((char*) v3 + 0x2d) |= 8;
	return 1;
}
