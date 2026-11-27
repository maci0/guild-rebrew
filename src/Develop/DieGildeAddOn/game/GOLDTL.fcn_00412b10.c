#include <string.h>
#include "../../Units/d3/d3_animation.h"
typedef struct D3_ANIM_KEYFRAME {
	unsigned int parameter;
	float position[3];
	char unknown_010[4];
	float rotation[3];
	char unknown_020[0x58 - 0x20];
} D3_ANIM_KEYFRAME;
extern int d3_ActiveCamera;
int* __cdecl d3_CreateObjectAnimation(char* a0, D3_ANIMATION_OPTIONS flags, int count, void* frames);
void __cdecl d3_WrapEulerAnglesPi(void* a0, void* a1, void* a2, void* a3);
void __cdecl d3_SetObjectRotation(void* a0, void* a1);

/* The native body keeps an EBP frame (/Oy-, non-frame-omitted build). */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00412b10 */
unsigned int __cdecl d3_AnimateObjectToTransform(
	char* object, float targetX, float targetY, float targetZ,
	float targetRotX, float targetRotY, float targetRotZ,
	unsigned int duration, unsigned char flags)
{
	D3_ANIMATION_OPTIONS z;
	float rotation[3];
	char v6[12];
	D3_ANIM_KEYFRAME frames[2];
	int* v3;
	void* fill_dst;
	int fill_size;

	if (*(int*) 0x6b5cbc != 0 && (char*) d3_ActiveCamera == object) {
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
	rotation[0] = targetRotX;
	z.layer = z.layer & 0xf7;
	z.queue = 1;
	rotation[2] = targetRotZ;
	frames[0].position[0] = 0.0f;
	frames[0].position[1] = 0.0f;
	frames[0].position[2] = 0.0f;
	frames[0].rotation[0] = 0.0f;
	frames[0].rotation[1] = 0.0f;
	frames[0].rotation[2] = 0.0f;
	rotation[1] = targetRotY;
	if ((flags & 8) != 0) {
		d3_WrapEulerAnglesPi(object + 0x84, rotation, v6, rotation);
		d3_SetObjectRotation(object, v6);
	}
	if (object == (char*) d3_ActiveCamera) {
		*(float*) 0x14ce890 = rotation[0];
		*(float*) 0x14ce894 = rotation[1];
		*(float*) 0x14ce898 = rotation[2];
		*(float*) 0x14ce880 = targetX;
		*(float*) 0x14ce884 = targetY;
		*(float*) 0x14ce888 = targetZ;
	}
	frames[1].position[0] = targetX - *(float*) (object + 0x4c);
	frames[1].position[1] = targetY - *(float*) (object + 0x50);
	frames[1].position[2] = targetZ - *(float*) (object + 0x54);
	frames[0].parameter = duration;
	rotation[0] -= *(float*) (object + 0x84);
	rotation[1] -= *(float*) (object + 0x88);
	rotation[2] -= *(float*) (object + 0x8c);
	frames[1].rotation[0] = rotation[0];
	frames[1].rotation[1] = rotation[1];
	frames[1].rotation[2] = rotation[2];
	v3 = d3_CreateObjectAnimation(object, z, 2, frames);
	if (object != (char*) d3_ActiveCamera) {
		return 1;
	}
	*(int*) 0x6b5cbc = 1;
	*(int**) 0x6b5cc0 = v3;
	*(unsigned char*) ((char*) v3 + 0x2d) |= 8;
	return 1;
}
