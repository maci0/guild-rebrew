#include <string.h>

/* SIZE 0x58 */
typedef struct
{
	int type;
	float pos[3];
	float f10;
	float rot[3];
	char pad20[0x38];
} FRAME;

/* SIZE 0xc */
typedef struct
{
	unsigned char b[12];
} FLAGS;

void __cdecl d3_TransformPoint(char* object, float* in, float* out);
int __cdecl d3_CreateObjectAnimation(char* obj, FLAGS fl, int n, FRAME* frames);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00414fb0 */
int __cdecl fcn_00414fb0(int* obj, int a, int b, void** list)
{
	FRAME frames[64];
	FLAGS fl;
	int q;
	int i;
	int cnt;
	void* e;

	{
		int fn;
		char* fp;

		fn = 0x1600;
		fp = (char*) frames;
		__asm {
			mov edi, fp
			mov ebx, fn
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
	}
	{
		char* fp;
		int fn;

		fn = 0xc;
		fp = (char*) &fl;
		__asm {
			mov edi, fp
			mov ebx, fn
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
	fl.b[1] |= 0x14;
	fl.b[8] |= 2;
	fl.b[1] |= 8;
	cnt = 1;
	q = a / b;
	frames[0].rot[0] = 0.0f;
	frames[0].rot[1] = 0.0f;
	frames[0].rot[2] = 0.0f;
	frames[0].pos[0] = 0.0f;
	frames[0].pos[1] = 0.0f;
	frames[0].pos[2] = 0.0f;
	frames[0].type = q;
	for (i = 0; i < b; i++) {
		e = list[i];
		if (e != 0) {
			d3_TransformPoint(e, (float*) ((char*) e + 0x4c), frames[i + 1].pos);
			frames[i + 1].rot[0] -= *(float*) ((char*) obj + 0x84);
			frames[i + 1].rot[1] -= *(float*) ((char*) obj + 0x88);
			frames[i + 1].rot[2] -= *(float*) ((char*) obj + 0x8c);
			frames[i + 1].pos[0] -= *(float*) ((char*) obj + 0x4c);
			frames[i + 1].pos[1] -= *(float*) ((char*) obj + 0x50);
			frames[i + 1].pos[2] -= *(float*) ((char*) obj + 0x54);
			frames[i].type = q;
			cnt++;
		}
	}
	frames[cnt].type = 0;
	return d3_CreateObjectAnimation((char*) obj, fl, b + 1, frames);
}
