#include <string.h>

typedef struct Deed {
	unsigned char type;
	char name[0x23];
	void* score;
	void* start;
	void* run;
	char pad30[0x60];
	int flags;
} Deed;
// SIZE 0x94

int __cdecl fcn_00494ed0(Deed* d, char* e);
int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl fcn_0048fc30(void);
int __cdecl fcn_0048fdd0(void);
int __cdecl fcn_0048fe70(void);
int __cdecl fcn_00490130(void);
int __cdecl fcn_004901b0(void);
int __cdecl fcn_004901c0(void);

/* ADDRESS: GOLD 0x00490c00 */
/* ADDRESS: GOLDTL 0x004901d0 */
int __cdecl fcn_004901d0(char* e)
{
	Deed d;

	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
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
	}
	d.type = 0x3d;
	strcpy(d.name, "Graveyard Owner");
	d.score = fcn_004a4410;
	d.start = fcn_0048fc30;
	d.run = fcn_0048fdd0;
	d.flags = 0x1c3;
	if (fcn_00494ed0(&d, e) == 0) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
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
	d.type = 0x3e;
	strcpy(d.name, "Handle Grave");
	d.score = fcn_004a4410;
	d.start = fcn_0048fe70;
	d.run = fcn_00490130;
	d.flags = 1;
	if (fcn_00494ed0(&d, e) == 0) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L3
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L3:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3f;
	strcpy(d.name, "Use Seance");
	d.score = fcn_004a4410;
	d.start = fcn_004901b0;
	d.run = fcn_004901c0;
	d.flags = 1;
	return fcn_00494ed0(&d, e) != 0;
}
