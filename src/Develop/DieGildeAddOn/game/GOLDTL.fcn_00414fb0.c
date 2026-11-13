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

void __cdecl fcn_00455350(char* object, float* in, float* out);
int __cdecl fcn_004339e0(char* obj, FLAGS fl, int n, FRAME* frames);

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

	__asm {
		mov edi, frames
		mov ebx, 0x1600
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
	__asm {
		mov edi, fl
		mov ebx, 0xc
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
	fl.b[1] |= 0x1c;
	fl.b[8] |= 2;
	q = a / b;
	cnt = 1;
	frames[0].type = q;
	for (i = 0; i < b; i++) {
		e = list[i];
		if (e != 0) {
			fcn_00455350(e, (float*) ((char*) e + 0x4c), frames[i + 1].pos);
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
	return fcn_004339e0((char*) obj, fl, b + 1, frames);
}
